<?php
/**
 * Script to count the idf(TF-IDF algorithm) value
 *	of all words in all the non-special lexicon file
 *
 * @author 	chenxin<chenxin619315@gmail.com>
*/

 //------------------------------------------------------------

//1. get all the lexicon files
$inputDir 	= '/c/products/friso/dict/UTF-8/';		//end with '/' please
$outputDir	= '/home/chenxin/dict/UTF-8/';
$logfile 	= '/home/chenxin/log.txt';

$handler	= opendir($inputDir);
if ( $handler == false )
{
	exit("Unable to open lexicon directory [$inputDir].\n");
}

$lexFiles 	= array();
while ( ($file = readdir($handler)) != false )
{
	if ( $file == '.' || $file == '..' ) continue;

	//get the file start with lex- and end with .lex
	if ( strncmp($file, 'lex-', 4) != 0 ) 	continue;
	if ( stripos($file, '.lex') === false )	continue;

	$lexFiles[] 	= $file;
}
unset($handler);


//open the log file
$logHandler 	= fopen($logfile, "wb");
if ( $logHandler == false )
{
	echo "Fail to open the error log file\n";
	exit();
} 


//get the totals number of documents
echo '+Try to get the totals documents.'."\n";
$totalDocuments 	= getDocumentsNumber('的');
echo "Total documents: {$totalDocuments}\n";


//Analysis each valid lexicon file
//and get the number of documents that contains the word
//	in each line of the lexicon file
foreach ( $lexFiles as $file ) 
{
	$srcFile = $inputDir . $file;
	echo '+-Try to analysis lexicon file ' . "$srcFile\n";

	$handler 	= fopen($srcFile, 'rb');
	if ( $handler == false )
	{
		echo("Unabe to open lexicon file: [$srcFile]\n");
		fputs($logHandler, "fail to analysis lexicon file {$srcFile}\n");
		continue;
	}


	//-------------------------------------------------------------
	//create the output file and analysis the lexicon file

	$dstFile 	= $outputDir . $file;
	$output 	= fopen($dstFile, 'wb');
	if ( $output == false )
	{
		fclose($handler);
		echo("Unable to create output lexicon file: [$dstFile]\n");
		continue;
	}

	//Analysis each line
	while ( ! feof( $handler ) )
	{
		$line 	= trim( fgets($handler) );

		//clear up the comments whitespace
		if ( $line 		== '' ) 	continue;
		if ( $line[0] 	== '#' ) 	continue;
		if ( strpos($line, '/') === false ) continue;

		$line 		= preg_replace('/\n{1,}/', '', $line);
		$splits 	= explode('/', $line);
		$word 		= $splits[0];

		//printf("+--Analysis word %s...\n", $word);
		color_println("+--Analysis word {$word}...");

		$number 	= getDocumentsNumber($word);
		if ( $number == false ) 
		{
			echo("Fail to get the documents count from google.\n");
			fputs($logHandler, "Fail to analysis word {$word} in lexicon file {$srcFile}\n");
			continue;
		}

		$idf 		= log($totalDocuments/($number + 1));
		if ( ($pos = strpos($idf, '.') ) !== false )
		{
			$idf 	= substr($idf, 0, $pos + 6);
		}

		echo '+---Appending the idf value:[' . $idf . "]\n";
		fputs($output, $line."/{$idf}\n");

		//yat, sleep for while, or google will get angry
		usleep(1000000);
	}

	echo "\n";

	fclose($handler);
	fclose($output);
}




//--------------------------------------------------------------------
//internal function to get the number of documents that
//contains the specifield words
function getDocumentsNumber( $word )
{
	$userAgent 	= <<<EOF
		Mozilla/5.0 (X11; Linux i686) AppleWebKit/535.19 (KHTML, like Gecko) 
		Ubuntu/10.10 Chromium/18.0.1025.151 Chrome/18.0.1025.151 Safari/535.19
EOF;

	//http://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=%E7%9A%84

/*	$api_url 	= 'https://www.google.com.hk/search';
	$api_url	.= '?oe=utf8&ie=utf8&source=uds&start=0&hl=zh-cn';
	$api_url	.= '&q=' . urlencode($word);*/
	$api_url 	= 'http://ajax.googleapis.com/ajax/services/search/web?v=1.0&q='.urlencode($word);

	$curl 		= curl_init();
	curl_setopt($curl, CURLOPT_HTTPGET, 			1);
	curl_setopt($curl, CURLOPT_URL, 				$api_url);  
	curl_setopt($curl, CURLOPT_HEADER, 				false);  
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, 		1);
	curl_setopt($curl, CURLOPT_DNS_USE_GLOBAL_CACHE,1);
	curl_setopt($curl, CURLOPT_USERAGENT, 			$userAgent);

	//get the http response
	$ret 		= curl_exec($curl);
	curl_close($curl);

	//$ret 		= file_get_contents($api_url);

	$data 		= json_decode($ret);
	unset($ret);

	if ( $data == null ) 				return false;
	if ( $data->responseStatus != 200 ) return false;

	return $data->responseData->cursor->estimatedResultCount;
}


//terminal color print
function color_println( $str )
{
	printf("\033[36m%s\033[0m\n", $str);
}
?>
