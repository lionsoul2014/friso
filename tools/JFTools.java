package org.lionsoul.cedict;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;

public class JFTools {
	
	public static final int JF_WORD = 1 << 0;
	public static final int JF_POS = 1 << 1;
	public static final int JF_PY = 1 << 2;
	public static final int JF_SYN = 1 << 3;
	
	/**
	 * change the jcseg lexicon file to friso lexicon file.
	 * 
	 * @param	j_dic
	 * @param	f_dic
	 * @param	keep
	 * @throws IOException 
	 */
	public static boolean invoke( File j_dic, File f_dic, int keep ) throws IOException 
	{
		BufferedReader reader = new BufferedReader(new FileReader(j_dic));
		BufferedWriter writer = new BufferedWriter(new FileWriter(f_dic));
		
		String line = null;
		reader.readLine();	//read the type
		while ( (line = reader.readLine()) != null ) 
		{
			line = line.trim();
			//comment or simple word
			if ( line.charAt(0) == '#'
					|| line.indexOf('/') == -1 ) {
				writer.write(line);
				writer.write('\n');
				continue;
			}
			
			String splits[] = line.split("/");
			if ( splits.length < 4 ) continue;
			StringBuffer sb = new StringBuffer();
			
			//Append the word
			if ( (keep & JF_WORD) != 0 ) { 
				sb.append(splits[0]);
			}
			
			//Append the part of speech
			if ( (keep & JF_POS) != 0 ) {
				if ( sb.length() > 0 ) 
					sb.append('/');
				sb.append(splits[1]);
			}
			
			//Append the pinyin]
			if ( (keep & JF_PY) != 0 ) {
				if ( sb.length() > 0 )
					sb.append('/');
				sb.append(splits[2]);
			}
			
			//Append the synomyms
			if ( (keep & JF_SYN) != 0 ) {
				if ( sb.length() > 0 )
					sb.append('/');
				sb.append(splits[3]);
			}
			
			//Append the single word degree.
			if ( splits.length > 4 ) {
				if ( sb.length() > 0 )
					sb.append('/');
				sb.append(splits[4]);
			}
			
			//Write the item
			writer.write(sb.toString());
			writer.write('\n');
			sb = null;
			line = null;
		}
		
		reader.close();
		writer.close();
		
		return true;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if ( args.length != 2 ) {
			System.out.println("Usage: java -jar JFTools.jar {jcseg.lex} {friso.lex}");
			System.out.println("{jcseg.lex}: jcseg lexicon directory.");
			System.out.println("{friso.lex}: friso lexicon directory");
			System.exit(1);
		}
		
		File srcDir = new File(args[0]);
		if ( ! srcDir.exists() ) {
			System.out.println("Error: No Such file or directory for " + args[0]);
			System.exit(1);
		}
		
		File dstDir = new File(args[1]);
		if ( ! dstDir.exists() ) {
			System.out.println("Error: No such file or directory for " + args[1]);
			System.exit(1);
		}
		
		//get the all the files.
		File[] files = srcDir.listFiles(new FilenameFilter(){
			@Override
			public boolean accept(File dir, String name) {
				return ( name.startsWith("lex")
							&& name.endsWith("lex"));
			}
		});
		
		//item to keep
		int keep = JF_WORD | JF_SYN;
		
		//show the confirm message.
		System.out.println("Opt: Jcseg词库转Friso词库: ");
		System.out.println("srcDir: " + srcDir.getAbsolutePath());
		System.out.println("dstDir: " + dstDir.getAbsolutePath());
		System.out.print("Execute?(Y/N): ");
		try {
			char opt = (char) System.in.read();
			if ( ! (opt == 'Y' || opt == 'y') ) {
				System.out.println("Operation was terminated.");
				System.exit(0);
			}
			
			int success = 0;
			//convert all the dictionary files.
			for ( int j = 0; j < files.length; j++ ) {
				System.out.format("+-Converting file %20s ... ", files[j].getName());
				if ( invoke(files[j], 
						new File(dstDir.getAbsolutePath()+"/"+files[j].getName()), keep)) {
					System.out.println("--[Ok]");
					success++;
				} else 
					System.out.println("--[Fail]");
			}
			System.out.println("+Done, Total [" + files.length+"], successfull convert [" + success + "]");
		
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
