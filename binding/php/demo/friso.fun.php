<?php
header("Content-Type:text/html;charset=utf-8;");

echo "constant access:<br />";
echo "complex mode: ".FRISO_COMPLEX.", simple mode: ".FRISO_SIMPLE."<br />";
echo "friso_ucode_utf8(20013)=".friso_ucode_utf8(20013)."<br />";
echo "friso_utf8_ucode(中)=".friso_utf8_ucode("中")."<br />";
echo "friso_utf8_bytes(中)=".friso_utf8_bytes("中")."<p />";

echo "词库函数：<br />";
echo "friso_dic_exist(研究) ? ".friso_dic_exist(FRISO_LEX_CJK, "研究")."<br />";

$_entry = friso_dic_get(FRISO_LEX_CJK, "你");
echo "friso_dic_get(你)：<br />";
echo "|——length: ".$_entry["length"].", freq: ".$_entry["freq"]."<p />";

//version about.
echo "friso_version(): " , friso_version(), ", friso_charset(): ", friso_charset(), "<p />";

echo "分词函数：<br />";
if ( friso_charset() == 'UTF-8' )
{
	$_str = "歧义和同义词:研究生命起源，混合词: 做B超检查身体，x射线本质是什么，今天去奇都ktv唱卡拉ok去，哆啦a梦是一个动漫中的主角，单位和全角: 2009年８月６日开始大学之旅，岳阳今天的气温为38.6℃, 也就是101.48℉, 英文数字: bug report chenxin619315@gmail.com or visit http://code.google.com/p/jcseg, we all admire the hacker spirit!特殊数字: ① ⑩ ⑽ ㈩.";
	echo "<p>friso_split(\"" . $_str . "\")：<p />";
	
	//API:
	//rb_split(string, Array, [long])
	//1.string: 要被切分的字符串。
	//2.Array: 配置选项，使用NULL来选择默认的配置(friso.ini中的配置)。
	//3.long: 可选参数，自定义切分返回选项，查看下面的$_rargs
	
	//1.完整的配置: 
	//array('max_len'=>5, 'r_name'=>0, 'mix_len'=>2, 'lna_len'=>1, 'add_syn'=>1,
	//	'clr_stw'=>1, 'keep_urec'=>0, 'spx_out'=>0, 'en_sseg'=> 1, 'st_minl'=>2, 'kpuncs'=>'.+#', 'mode'=>FRISO_COMPLEX);
	//1.在不了解friso内核的情况下, 请不要随便更改nthreshold
	//2.使用NULL来使用php.ini中指定的friso.ini文件中的配置
	
	//2.返回选项：
	//词条: FRISO_RET_WORD, 类别：FRISO_RET_TYPE, 长度：FRISO_RET_LENGTH, 真实长度：FRISO_RET_RLEN, 偏移量：FRISO_RET_OFF
	//词性：FRISO_RET_POS(待实现)
	$_rargs = FRISO_RET_TYPE | FRISO_RET_LEN | FRISO_RET_RLEN | FRISO_RET_OFF | FRISO_RET_POS;
	//$_rargs = 0;
	
	//3.切分类别：
	//CJK词条：FRISO_TYP_CJK, 英中混合词(b超)：FRISO_TYP_ECM，中英混合词(卡拉ok)：FRISO_TYP_CEM，
	//英文标点混合词(c++)：FRISO_TYP_EPUN，标点：FRISO_TYP_PUN，未知类别：FRISO_TYP_UNK，其他类别(同义词)：FRISO_TYP_OTR
	$_result = friso_split($_str, array('mode'=>FRISO_COMPLEX), $_rargs);
	unset($_str);
	foreach ( $_result as $_val )
	{
		$_str = $_val['word'];
		if ( $_rargs != 0 ) {
			$_str .= '[';
			if ( ($_rargs & FRISO_RET_TYPE) != 0 )
				$_str .= ', type: '.$_val['type'];		//获取词条类别
			if ( ($_rargs & FRISO_RET_LEN) != 0 )
			$_str .= ', len: ' . $_val['len'];			//词条长度
			if ( ($_rargs & FRISO_RET_RLEN) != 0 )
			$_str .= ', rlen: ' . $_val['rlen'];		//词条真实长度
			if ( ($_rargs & FRISO_RET_OFF) != 0 )
			$_str .= ', off: ' . $_val['off'];			//词条偏移量
			if ( ($_rargs & FRISO_RET_POS) != 0 )
				$_str .= ', pos: ' . $_val['pos'];		//词条词性
			$_str .= ']';
		}

		$_str .= '/&nbsp;&nbsp;&nbsp;';
		echo $_str;
	}
}
else echo "set charset to UTF-8 to test function friso_split.";
?>
