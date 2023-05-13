## 正则匹配
### /**/
* 只能匹配一行
```re
(\/\*.*?\*\/) 
```
* 匹配多行
```re
(\/\*(\s|.)*?\*\/)
```
### //匹配
```re
(\/\/.*?\s)
```

## 语义分析
* 每次遇到一个复合语句的结点COM_STM，
    * 首先对LEV加1，表示准备进入一个新的作用域
    * 为了管理这个作用域中的变量，使用栈symbol_scope_TX，记录该作用域变量在符号表中的起点位置，即将符号表symbolTable的栈顶位置symbolTable.index保存在栈symbol_scope_TX中。
    * 每次遍历完一个复合语句结点COM_STM的所有子树，准备回到其父结点时，这时该复合语句语义分析完成，需要从符号表中删除该复合语句的变量，方法是首先symbol_scope_TX退栈，取出该复合语句作用域的起点，再根据这个值修改symbolTable.index，同时LEV减一，很简单地完成了符号表的符号删除操作。
* 每次要登记一个新的符号到符号表中时，
    * 首先在symbolTable中，从栈顶向栈底方向查层号为LEV的符号，是否有和当前待登记的符号重名，是则报重复定义错误，

    * 否则使用LEV作为层号将新的符号登记到符号表中