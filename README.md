# **Friso**是什么？

Friso 是使用 c 语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，
例如：MySQL，PHP，并且提供了php5, php7, ocaml, lua的插件实现。源码无需修改就能在各种平台下编译使用，加载完 20 万的词条，内存占用稳定为 14.5M.


# **Friso**核心功能：

- [x] 中文分词：mmseg算法 + **Friso** 独创的优化算法，四种切分模式。
- [ ] 关键字提取：基于textRank算法。
- [ ] 关键短语提取：基于textRank算法。
- [ ] 关键句子提取：基于textRank算法。


# **Friso**中文分词：

### 四种切分模式：

- [x] 简易模式：FMM 算法，适合速度要求场合。
- [x] 复杂模式- MMSEG 四种过滤算法，具有较高的岐义去除，分词准确率达到了98.41%。
- [x] 检测模式：只返回词库中已有的词条，很适合某些应用场合。(1.6.1版本开始)。
- [ ] 最多模式：细粒度切分，专为检索而生，除了中文处理外（不具备中文的人名，数字识别等智能功能）其他与复杂模式一致（英文，组合词等）。

### 分词功能特性：
- [x] 同时支持对 UTF-8/GBK 编码的切分，支持 php5 和 php7 扩展和 sphinx token 插件。
- [x] 支持自定义词库。在 dict 文件夹下，可以随便添加/删除/更改词库和词库词条，并且对词库进行了分类。
- [x] 简体/繁体/简体混合支持, 可以方便的针对简体，繁体或者简繁体切分。同时还可以以此实现简繁体的相互检索。
- [x] 支持中英/英中混合词的识别(维护词库可以识别任何一种组合)。例如：卡拉ok, 漂亮mm, c语言，IC卡，哆啦a梦。
- [x] 很好的英文支持，英文标点组合词识别, 例如c++, c#, 电子邮件，网址，小数，百分数。
- [x] 自定义保留标点：你可以自定义保留在切分结果中的标点，这样可以识别出一些复杂的组合，例如：c++, k&r，code.google.com。
- [x] 复杂英文切分的二次切分：默认 Friso 会保留数字和字母的原组合，开启此功能，可以进行二次切分提高检索的命中率。例如：qq2013会被切分成：qq/ 2013/ qq2013。
- [x] 支持阿拉伯数字/小数基本单字单位的识别，例如2012年，1.75米，5吨，120斤，38.6℃。
- [x] 自动英文圆角/半角，大写/小写转换。
- [x] 同义词匹配：自动中文/英文同义词追加. (需要在 friso.ini 中开启 friso.add_syn 选项)。
- [x] 自动中英文停止词过滤。(需要在 friso.ini 中开启 friso.clr_stw 选项)。
- [x] 多配置支持, 安全的应用于多进程/多线程环境。


# **Friso**快速体验：

#### 终端测试：

1. cd到 **Friso**根目录。
2. make
3. 运行：./src/friso -init ./friso.ini
4. 你将看到类似如下的终端界面
5. 在光标处输入文本开始测试

```
Initialized in 0.088911sec
Mode: Complex
+-Version: 1.6.2 (UTF-8)
+---------------------------------------------------------------+
| Friso - a Chinese word segmentation writen by c.              |
| bug report email - chenxin619315@gmail.com.                   |
| or: visit https://github.com/lionsoul2014/friso.              |
|     java edition for https://github.com/lionsoul2014/jcseg    |
| type 'quit' to exit the program.                              |
+---------------------------------------------------------------+
friso>> 
```

#### 测试样板：

##### 分词文本

~~~text
歧义和同义词:研究生命起源，混合词: 做B超检查身体，x射线本质是什么，今天去奇都ktv唱卡拉ok去，哆啦a梦是一个动漫中的主角，单位和全角: 2009年８月６日开始大学之旅，岳阳今天的气温为38.6℃, 也就是101.48℉, 英文数字: bug report example@gmail.com or visit http://code.google.com/p/jcseg, we all admire the hacker spirit!特殊数字: ① ⑩ ⑽ ㈩.
~~~

##### 分词结果：

~~~text
歧义 和 同义词 : 研究 琢磨 研讨 钻研 生命 起源 ， 混合词 : 做 b超 检查 身体 ， x射线 本质 是 什么 ， 今天 去 奇都ktv 唱 卡拉ok 去 ， 哆啦a梦 是 一个 动漫 中 的 主角 ， 单位 和 全角 : 2009年 8月 6日 开始 大学 之旅 ， 岳阳 今天 的 气温 为 38.6℃ , 也就是 101.48℉ , 英文 英语 数字 : bug report example gmail com example@gmail.com or visit http : / / code google com code.google.com / p / jcseg , we all admire appreciate like love enjoy the hacker spirit mind ! 特殊 数字 : .
~~~



# Friso安装

### Linux:
cd到friso的根目录，运行：
```shell
make
sudo make install

# for testing
make testing
```
备注：如果是 64 位的系统，请将/usr/lib/libfriso.so 拷贝一份到/usr/lib64 中

### Winnt:
1. 使用 VS 编译得到 dll 和 lib 文件，具体可以参考 Friso 讨论：http://www.oschina.net/question/853816_135216
2. 使用 cygwin 从源码编译； 删除原有的 Makefile, 更改 Makefile.cygwin 为 Makefile, 打开 cygwin 的终端，cd 到 Friso 的 src 目录，运行:
```shell
make
```
备注：在Friso的src目录下即可得到friso.exe和friso.dll文件。




# Friso配置
Friso 要做的配置工作很简单，找到 friso.ini 配置文件, 使用文本编辑器打开即可

### 配置说明：

```
# friso configuration file.
#	do not change the name of the left key.
# @email	chenxin619315@gmail.com
# @date		2012-12-20
#

# charset, only UTF8 and GBK support.
# set it with UTF8(0) or GBK(1)
friso.charset = 0

# lexicon directory absolute path.
#	the value must end with '/'
# this will tell friso how to find friso.lex.ini configuration file and all the lexicon files.
#
# if it is not start with '/' for linux, or matches no ':' for winnt in its value 
#	friso will search the friso.lex.ini relative to friso.ini
# absolute path search:
# linux:	friso.lex_dir = /c/products/friso/dict/UTF-8/
# Winnt:	friso.lex_dir = D:/products/friso/dict/UTF-8/
# relative path search (All system)
friso.lex_dir = ./vendors/dict/UTF-8/

# the maximum matching length.
friso.max_len = 5 

# 1 for recognition chinese name.
#	and 0 for closed it.
friso.r_name = 1

# the maximum length for the cjk words in a
#	chinese and english mixed word.
friso.mix_len = 2

# the maxinum length for the chinese last name adron.
friso.lna_len = 1

# append the synonyms words
friso.add_syn = 1

# clear the stopwords or not (1 to open it and 0 to close it)
# @date 2013-06-13
friso.clr_stw = 0

# keep the unrecongized words or not (1 to open it and 0 to close it)
# @date 2013-06-13
friso.keep_urec = 0

# use sphinx output style like 'admire|love|enjoy einsten'
# @date 2013-10-25
friso.spx_out = 0

# start the secondary segmentation for complex english token.
friso.en_sseg = 1

# min length of the secondary segmentation token. (better larger than 1)
friso.st_minl = 2

# default keep punctuations for english token.
friso.kpuncs = @%.#&+

# the threshold value for a char not a part of a chinese name.
friso.nthreshold = 2000000

# default mode for friso.
# 1 : simple mode - simply maxmum matching algorithm.
# 2 : complex mode - four rules of mmseg alogrithm.
# 3 : detect mode - only return the words that the do exists in the lexicon
friso.mode = 2
```

### 词库的配置：

1. friso.ini中 friso.lex_dir 指向friso依赖的词库目录, 修改其值为词库目录绝对地址, 并且必须以”/”结尾。例如：friso.lex_dir = /usr/lib/friso/dict/
2. 词库分为UTF-8和GBK编码的，根据你使用的编码需要选择加载对应编码的词库。




# Friso插件

Friso目前提供了对php5, php7, ocaml, lua的分词插件：

语言 | binding | 作者 | 状态
:-: | :-: | :-: | :-:
php | [php5-binding](binding/php5) | dongyado&lt;dongyado@gmail.com&gt; | 已完成
php | [php7-binding](binding/php7) | dongyado&lt;dongyado@gmail.com&gt; | 已完成
ocaml | [ocaml-binding](binding/ocaml) | https://github.com/kandu | 已完成
sphinx | [sphinx-binding](binding/sphinx) | lionsoul&lt;chenxin619315@gmail.com&gt; | 开发中
lua | [lua-binding](binding/lua) | lionsoul&lt;chenxin619315@gmail.com&gt; | 开发中



# Friso分词接口

### 一个完整的demo: 
```c
/* 第一步：申明三个对象 */
friso_t friso;          /* Friso 分词对象 */
friso_config_t config;  /* Friso 配置对象 */
friso_task_t task;      /* Friso 任务对象 */

/* 第二步：初始化相应的对象 */
friso  = friso_new();
config = friso_new_config();
task   = friso_new_task();

/* 从friso.ini配置文件中初始化 friso */
if (friso_init_from_ifile(friso, config, "friso.ini文件地址") != 1) {
    /* friso 初始化失败 */
}

/*
 * 切分模式默认来自friso.ini中的设置
 * 可以通过friso_set_mode函数自定义切分模式(简易，复杂，检测模式)
 * 简易模式：__FRISO_SIMPLE_MODE__
 * 复杂模式：__FRISO_COMPLEX_MODE__
 * 检测模式：__FRISO_DETECT_MODE__
 * 例如，这里设置为使用复杂模式分词：
*/
friso_set_mode(config, __FRISO_COMPLEX_MODE__);


/* 第三步：设置分词内容 */
friso_set_text(task, "分词的文本");

/* 第四步：获取分词内容 */
while (config->next_token(friso, config, task) != NULL) {
    /* 
      task存储了分词的结果，
      task->token->word: 词条内容
      task->token->offset: 词条在原始文本的offset
      task->token->length: 词条的长度(字节数)
      task->token->rlen: 词条的真正字节数(Friso转换后的长度-字节数)
    */
    printf("%s ", task->token->word);
}


/* 第五步：释放对象 */
friso_free_task(task);
friso_free_config(config);
friso_free(friso);
```

### 备注：
1. 第三步和第四步可以反复调用，使用friso_set_setx重置分词内容即可。
2. 对于多线程环境，不同线程共享friso和config对象，需要分别初始化task使用对象。





# Friso词库管理

### 词库分类定义

Friso 内部对词库进行了分类, 在管理词库前你需要先了解Friso的词库类别，分类整型值以及含义如下：

```
typedef enum {
 __LEX_CJK_WORDS__ = 0,     // 普通 CJK 词库
 __LEX_CJK_UNITS__ = 1,     // CJK 单位词库
 __LEX_ECM_WORDS__ = 2,     // 英中混合词(例如: b 超)
 __LEX_CEM_WORDS__ = 3,     // 中英混合词(例如: 卡拉 ok).
 __LEX_CN_LNAME__  = 4,     // 中文姓氏
 __LEX_CN_SNAME__  = 5,     // 中文单姓名词库
 __LEX_CN_DNAME1__ = 6,     // 中文双姓名首字词库
 __LEX_CN_DNAME2__ = 7,     // 中文双姓名尾字词库
 __LEX_CN_LNA__ = 8,        // 中文姓氏修饰词词库
 __LEX_STOPWORDS__ = 9,     // 停止词词库
 __LEX_ENPUN_WORDS__ = 10,  // 英文和标点混合词库(例如: c++)
 __LEX_OTHER_WORDS__ = 15,  // 无用
 __LEX_NCSYN_WORDS__ = 16   // 无用
} friso_lex_t;
```

### 词库配置文件

词库目录下的 friso.lex.ini 配置文件存储了词库类别以及对应类别下的词库文件名称，是一对多的关系，默认的配置如下：
```
# main lexion
__LEX_CJK_WORDS__ :[
    lex-main.lex;
    lex-admin.lex;
    lex-chars.lex;
    lex-cn-mz.lex;
    lex-cn-place.lex;
    lex-company.lex;
    lex-festival.lex;
    lex-flname.lex;
    lex-food.lex;
    lex-lang.lex;
    lex-nation.lex;
    lex-net.lex;
    lex-org.lex;
    lex-touris.lex;
# add more here
]
# single chinese unit lexicon
__LEX_CJK_UNITS__ :[
    lex-units.lex;
]
# chinese and english mixed word lexicon like "b超".
__LEX_ECM_WORDS__:[
    lex-ecmixed.lex;
]
# english and chinese mixed word lexicon like "卡拉ok".
__LEX_CEM_WORDS__:[
    lex-cemixed.lex;
]
# chinese last name lexicon.
__LEX_CN_LNAME__:[
    lex-lname.lex;
]
# single name words lexicon.
__LEX_CN_SNAME__:[
    lex-sname.lex;
]
# first word of a double chinese name.
__LEX_CN_DNAME1__:[
    lex-dname-1.lex;
]
# second word of a double chinese name.
__LEX_CN_DNAME2__:[
    lex-dname-2.lex;
]
# chinese last name decorate word.
__LEX_CN_LNA__:[
    lex-ln-adorn.lex;
]
# stopwords lexicon
__LEX_STOPWORDS__:[
    lex-stopword.lex;
]
# english and punctuation mixed words lexicon.
__LEX_ENPUN_WORDS__:[
    lex-en-pun.lex;
]
# english words(for synonyms words)
__LEX_EN_WORDS__:[
    lex-en.lex;
]
```

### 新增词库文件

1. 确认类别：首先确认你要加入的词库文件的类别. 
2. 新建词库：例如: 我想添加一个词库文件专门用来存储植物的名字, 在dict/下新建 lex-plants.lex文件, 然后按照一个词条一行的规则加入词条到该文件中.
3. 启用词库：接下来还有一个重要的步骤就是将该词库归类到 friso.lex.ini 中去, 通常的词库都是 CJK 词库, 也就是将lex-plants.lex 作为一行加入到 __LEX_CJK_WORDS__ 类别下即可。

```
# main lexion
__LEX_CJK_WORDS__ :[
    lex-main.lex;
    lex-admin.lex;
    lex-chars.lex;
    lex-cn-mz.lex;
    lex-cn-place.lex;
    lex-company.lex;
    lex-festival.lex;
    lex-flname.lex;
    lex-food.lex;
    lex-lang.lex;
    lex-nation.lex;
    lex-net.lex;
    lex-org.lex;
    lex-touris.lex;
# 新增的植物名称词库
    lex-plants.lex;
# add more here
]
```

### 给词库新增词条

找到对应的词库文件, 使用文本编辑器打开, 将要加入的词条按照下面的格式作为一行加入即可(备注：加入前建议先确认下相同的词条不存在)。

Friso 词库词条格式:

```
词条/同义词集合
```

同义词没有使用 null 代替, 多个同义词使用英文逗号隔开，例如：

```
你好/null
研究/琢磨,研讨,钻研
```




# 相关附录


### 参考文献

1. MMSEG算法原著：http://technology.chtsai.org/mmseg/

### 技术交流分享

1. 旧版的参考pdf参考文献：请参考项目下的 friso-help-doc.pdf
2. 使用案例典范：[RediSearch~信息检索](https://github.com/RediSearch/RediSearch)
3. NLP交流分享：微信：lionsoul2014(请备注Friso)，ＱＱ：1187582057(很少关注)
