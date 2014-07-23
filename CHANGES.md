<pre>
friso-1.6.2:

1. sphinx token filter

1. 复杂中文的二次切分

2. autotools支持

3. friso deb | rmp支持：
   Debian & Ubuntu:
	sudo apt-get install libfriso0 libfriso-dev
   CentOS & Fedora:
	sudo yum install libfriso libfriso-devel

4. 中文词性标注。

5. 中文数字识别。

6. 中文数字转阿拉伯数字。

7. 中文姓名识别。

8. 词库更新自动加载。


friso-1.6.1:

1. friso.ini中friso.lex_dir增加相对friso.ini的路径支持			-done

2. 修复两处内存泄漏bug.											-done

3. 改善中英混合词的识别, 可以识别更多情况, 例如:高3				-done

4. 词库优化, 加入了一些新词条.									-done

5. 修复friso_dic_add & array_list_insert的两处代码bug			-done

6. 增加检测模式切分, 只返回词库中有的词条						-done

7. 集成了php扩展绑定，完美支持PHP分词						-done



friso-1.6.0:

1. friso_stirng.c#utf8_decimal_string初始化bytes = 0, 
	去除WinNT的Run-Time Check Failed.											-done

2. 复杂英文和数字组合的二次切分. 例如: QQ2013会被切分成: qq2013, qq, 2013.		-done

3. GBK编码支持.																	-done

4. 增加了friso.ini中自定义保留标点, 去除了默认对"^,/,-,'"等标点的保留.			-done

5. 使用掩码操作控制变量来代替了原来的多个控制变量.								-done

6. 切分结果friso_hits_t中增加了对词条类别和词条长度的返回，纠正了offset的误差。	-done

7. 做了一些优化，例如：同义词的追加(普通/sphinx定义)复杂的判断逻辑，
	改为了使用掩码状态控制，不仅减少了代码量还提高了执行效率。					-done

8. 更多的返回信息，增加了对切分词条的类别，长度，真实长度，词性(待实现)等信息的返回。		-done

9. 增加了安装中头文件的自动拷贝（usr/include/friso），可以通过include <friso/xx.h>来引用头文件。


friso-1.5:

1. 加入sphinx定制输出, 同义词使用"|"串接, 例如: 研究|琢磨|研讨|钻研 生命

2. 修正了全部的tst-xxx源文件. friso API更改后测试样本文件没更改.

3. 修复friso.c#next_basic_latin中"数字+空格+单位"组合中忽略空格直接组合数字和单位的bug

4. 修复friso.c#next_basic_latin中"数字+中文+空格"组合切分乱码的bug

5. 引入friso_config_t多配置使用避免全局配置带来的更改不便.


friso-1.4:

1. 小数+单位无法识别的情况.更改friso_string#utf8_numeric_string()函数.

2. 更改中英混合词的识别(目前可以识别中英任何一种组合).
	英中: 例如: b超,
	英中英: a美1,
	英中英中: a哆啦a梦,
	中英: 卡拉ok, 
	中英中: 哆啦a梦, 
	中英中英: 中文a美a

3. 更改了单位组合, 现在可以组合的单位不局限是中文, 例如: ℃,℉

4. 对于未识别的字符, 给定一个开关选项来决定保留还是过滤.

5. 英文同义词的追加(增加了lex-en.lex词库)	


friso-1.3:
1. 除去和c++,vs的冲突(string和__value)

2. 部分简易函数使用了宏定义来代替, 减少函数的调用.

3. 保留了英文全半角和中文标点符号的切分.(可以通过过滤停止词来过滤不需要的标点)
	停止词词库中已经加入了全部的保留的标点, 也就是默认全部过滤了.

4. 修复friso_string#utf8_en_punctuation()函数一处bug.

5. 修复切分结果偏移量bug.(以这个词的开始索引作为offset)

6. 修复friso_lexicon#friso_dic_load一处bug.

7. 新增了对c++,c#类词条的识别.(新增lex-en-pun.lex词库)

8. 新增了中英混合词的识别, 例如: 卡拉ok(新增lex-cemix.lex词库)

9. 更改了Makefile, 优化了clean目标并且兼容64bit系统的编译.

10. 更改了词库, 加入了些许新词并且去掉了一些无用词.

11. 加入了friso开发帮助文档.pdf


friso-1.2:

1. 修复了一处在WinNT系统中会导致英文的切分结果无法获取bug. 之前忘记在WinNT系统中测试了.

2. 提供了linux和WinNT共享库文件, 尤其是WinNT系统的, 方便直接对friso接口进行调用.

3. 提供了cygwin的Makefile - Makefile.cygwin, 在WinNT系统下请使用该Makefile来编译friso

4. 重新整合了jcseg的词库, 加入了些许新词.

5. 加入了CHANGES文档,在README文档中加入了测试配置说明.


friso-1.1:

加入如下两个功能:

1. 修复了一个可能会导致内存泄漏的bug. 更改了接口API, 解决需要调用程序需要自动释放内存的问题, 在friso_next内自动处理了, 详细可查看官方文档.

2. 加上了同义词切分功能, 实现同义词匹配. (需要在friso.ini中配置friso.add_syn=1)

3. 加入了停止词过滤功能, 新加入了lex-stopwords.lex词库, 专门存放停止词词库. 

4. 对friso内部代码进行了优化, 加载全部词库只需13.xM内存, 而且切分速度也提高了. 简易模式可达: 3.8M/sec, 复杂模式也接近了2.0M/sec.


friso-1.0:

1。目前最高版本：friso 1.0，只支持UTF-8编码。

2。mmseg四种过滤算法，分词准确率达到了98.41%。

3。支持自定义词库。在dict文件夹下，可以随便添加/删除/更改词库和词库词条，并且对词库进行了分类。

4。词库使用了friso的Java版本jcseg的简化词库。

5。支持中英混合词的识别。例如：c语言，IC卡。

7。很好的英文支持，电子邮件，网址，小数，分数，百分数。

8。支持阿拉伯数字基本单字单位的识别，例如2012年，5吨，120斤。

9。自动英文圆角/半角，大写/小写转换。
</pre>
