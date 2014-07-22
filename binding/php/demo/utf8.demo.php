<?php
header('content-type:text/html;charset:utf-8');
ini_set('magic_quotes_gpc', 0);

//charset check.
if ( friso_charset() != "UTF-8" ) {
	$_str  = "Error: UTF-8 charset required. <br />";
	$_str .= "1. Modified friso.charset = 0 in your friso.ini .<br />";
	$_str .= "2. Modified friso.lex_dir = UTF-8 lexicon abusolute path to load your UTF-8 lexicon. <br />";
	exit($_str);
}

$text = '';
$_timer = 0;
$_act = '';
$_cfg = array('mode' => FRISO_COMPLEX);
if ( isset($_POST['_act']) && ($_act = $_POST['_act']) == 'split' ) {
	$text = &$_POST['text'];
	$_cfg = &$_POST['config'];
	if ( ! isset($_cfg['add_syn']) )	$_cfg['add_syn'] = 0;
	if ( ! isset($_cfg['clr_stw']) )	$_cfg['clr_stw'] = 0;
	if ( ! isset($_cfg['keep_urec']) )	$_cfg['keep_urec'] = 0;
	if ( ! isset($_cfg['spx_out']) )	$_cfg['spx_out'] = 0;
	if ( ! isset($_cfg['en_sseg']) )	$_cfg['en_sseg'] = 0;
	
	$s_time = timer();
	$_ret = friso_split($text, $_cfg);
	$_timer = timer() - $s_time;
}

function timer() {
	list($msec, $sec) = explode(' ', microtime());	
	return ((float)$msec + (float)$sec);
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<head>
	<title>UTF8 - robbe分词测试程序</title>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<style type="text/css">
		#box {width: 1000px}
		.input-text {border: 1px solid #CCC;width: 1000px;height: 180px;background-color: #FFF;
			color: #555;font-size: 14px;}
		.link-box {overflow: hidden;zoom:1;padding-top:10px;}
		#submit-link {float:right;width:150px;height: 26px;line-height: 26px;
			background-color: #A50100;color: #FFF;font-weight: bold;text-align: center;
			text-decoration: none;font-size: 14px;}
		#info-link {float:right;width:300px;height: 26px;line-height: 26px;
			background-color: #A50100;color: #FFF;font-weight: bold;text-align: center;
			text-decoration: none;font-size: 14px;}
		.link-item {float: left;font-size: 14px;font-weight: bold;
			height: 26px;line-height: 26px;width: 100px;color: #A50100;}
		.title-item {height:30px;line-height: 30px;font-size: 14px;font-weight: bold;}
		
		#cfg-box {margin-bottom: 10px;}
		#cfg-box div {overflow: hidden;zoom:1;color:#555;font-size:12px;}
		#cfg-box div label {float: left;width: 160px;height: 26px;line-height:26px;text-align:right;
			padding-right:10px;font-size:12px;font-weight:bold;color:#555;}
		.input {border: 1px solid #DDD;height: 18px;line-height: 18px;padding-left: 5px;width: 120px;
			color:#555; outline: none;}
	</style>
</head>

<body>
	<div id="box">
		<form name="robbe" method="post" action="utf8.demo.php">
		<div class="title-item">分词配置：</div>
		<div id="cfg-box">
			<div>
				<label>最大词长: </label>
				<input type="text" name="config[max_len]" value="<?=isset($_cfg['max_len'])?$_cfg['max_len']:5?>" class="input" />
			</div>
			<div>
				<label>混合词中文词长: </label>
				<input type="text" name="config[mix_len]" value="<?=isset($_cfg['mix_len'])?$_cfg['mix_len']:2?>" class="input" />
			</div>
			<div>
				<label>英文二次切分: </label>
				<input type="checkbox" name="config[en_sseg]" <?=isset($_cfg['en_sseg'])&&$_cfg['en_sseg']==1?'checked="checked"':''?> value="1" />
			</div>
			<div>
				<label>二次切分子Token最小长度: </label>
				<input type="text" name="config[st_minl]" value="<?=isset($_cfg['st_minl'])?$_cfg['st_minl']:2?>" class="input" />
			</div>
			<div>
				<label>英文Token中保留的标点: </label>
				<input type="text" name="config[kpuncs]" value="<?=isset($_cfg['kpuncs'])?$_cfg['kpuncs']:'@%.#&+'?>" class="input" />
			</div>
			<div>
				<label>同义词追加: </label>
				<input type="checkbox" name="config[add_syn]" <?=isset($_cfg['add_syn'])&&$_cfg['add_syn']==1?'checked="checked"':''?> value="1" />
			</div>
			<div>
				<label>过滤停止词: </label>
				<input type="checkbox" name="config[clr_stw]" <?=isset($_cfg['clr_stw'])&&$_cfg['clr_stw']==1?'checked="checked"':''?> value="1" />
			</div>
			<div>
				<label>保留未识别词: </label>
				<input type="checkbox" name="config[keep_urec]" <?=isset($_cfg['keep_urec'])&&$_cfg['keep_urec']==1?'checked="checked"':''?> value="1" />
			</div>
			<div>
				<label>sphinx定制输出: </label>
				<input type="checkbox" name="config[spx_out]" <?=isset($_cfg['spx_out'])&&$_cfg['spx_out']==1?'checked="checked"':''?> value="1" />
			</div>
			<div>
				<label>分词模式: </label>
				<input type="radio" name="config[mode]" value="<?=RB_SMODE?>" <?=isset($_cfg['mode'])&&$_cfg['mode']==1?'checked="checked"':''?> />简易模式
				<input type="radio" name="config[mode]" value="<?=RB_CMODE?>" <?=isset($_cfg['mode'])&&$_cfg['mode']==2?'checked="checked"':''?> />复杂模式
			</div>
		</div>
		
		<div class="title-item">分词内容：</div>
		<div class="r-item"><textarea name="text" class="input-text" id="text"><?=$text?></textarea></div>
		<input type="hidden" name="_act" value="split"/>
		<a href="javascript:;" onclick="do_submit();return false;" id="submit-link">robbe分词</a>
		</form>

		<?php
		if ( $_act == 'split' ) {
		?>
		<div class="title-item">分词结果：</div>
		<div><textarea class="input-text"><?php foreach ( $_ret as $_val ) echo $_val['word'].' ';?>
		</textarea></div>
		<div class="link-box"><a id="info-link">
			<?php
			$len = strlen($text);
			if ( $len >= 1048576 ) {
				echo substr(($len/1048576), 0, 6).'MB';
			} else if ( $len >= 1024 ) {
				echo substr( ($len / 1024), 0, 6).'KB';
			} else {
				echo $len.'B';
			}
			?>
			&nbsp;&nbsp;&nbsp;<?php printf("%.5f", $_timer)?>sec
		</a></div>
		<?php
		}
		?>
	</div>

<script type="text/javascript">
String.prototype.trim = function() {return this.replace(/^\s+|\s+$/g, '');}
function do_submit() {
	var text = document.getElementById('text');
	if ( text.value.trim() == '' ) return; 
	document.robbe.submit();
}
</script>
</body>
