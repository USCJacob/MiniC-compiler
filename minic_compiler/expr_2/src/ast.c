#include "def.h"
#include "parser.tab.h"
struct symboltable symtabs = {{0}, 0};
struct symbol_scope_begin symbol_index = {{0}, 0};
int var_count = 0;
int func_pos = 0;

struct ASTNode *mknode(int num, int kind, int pos, ...)
{
    struct ASTNode *T = (struct ASTNode *)calloc(sizeof(struct ASTNode), 1);
    int i = 0;
    T->kind = kind;
    T->pos = pos;
    va_list pArgs;
    va_start(pArgs, pos);
    for (i = 0; i < num; i++)
        T->ptr[i] = va_arg(pArgs, struct ASTNode *);
    while (i < 4)
        T->ptr[i++] = NULL;
    va_end(pArgs);
    return T;
}
void display_symbol_table(){
    printf("\t\tSymbol table\t\t\n");
    printf("%s\t%-8s\t%-10s\t%-10s\t%-10s\t%-10s\n","Index","Name","Level","Type","Flag","Param_num");
    for(int i=0;i<symtabs.index;i++){
        printf("%-5d\t",i);
        printf("%-8s\t",symtabs.symbols[i].name);
        printf("%-10d\t",symtabs.symbols[i].level);
        if(symtabs.symbols[i].type == INT){
            printf("%-10s\t","int");
        }
        else if (symtabs.symbols[i].type == FLOAT)
        {
            printf("%-10s\t","float");
        }else
        {
            printf("%-10s\t","char");
        }
        printf("%-10c\t",symtabs.symbols[i].flag);
        if(symtabs.symbols[i].flag == 'F'){
            printf("%-5d\t",symtabs.symbols[i].paramnum);
        }
        printf("\n");
    }
    printf("---------------\n");
}
//添加符号
void input_symbol(struct ASTNode* T,int type,int level,int flag)
{
    //从栈顶开始查找,找到当前层的启始位置
    int index = symtabs.index-1;
    while (index >= 0 && index < symtabs.index && symtabs.symbols[index].level == level)
    {
        index--;
    }
    index++;
    while (index < symtabs.index)
    {
        //重名
        if (strcmp(T->type_id, symtabs.symbols[index].name) == 0 )
        {
            if (type == symtabs.symbols[index].type)
            {
                printf("ERROR! line:%d,redeclaration, %s\n", T->pos, T->type_id);
            }
            else
            {
                printf("ERROR! line:%d, conflicting types for '%s'\n", T->pos, T->type_id);
            }
        }
        index++;
    }
    strcpy(symtabs.symbols[symtabs.index].name, T->type_id);
    symtabs.symbols[symtabs.index].level = level;
    symtabs.symbols[symtabs.index].type = type;
    symtabs.symbols[symtabs.index].flag = flag;
    symtabs.index++;
}
void display(struct ASTNode *T, int indent)
{ //对抽象语法树的先根遍历
    int i = 1;
    struct ASTNode *T0;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            display(T->ptr[0], indent); //显示该外部定义（外部变量和函数）列表中的第一个
            display(T->ptr[1], indent); //显示该外部定义列表中的其它外部定义
            break;
        case EXT_VAR_DEF:
            printf("%*c外部变量定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示外部变量类型
            printf("%*c变量名：\n", indent + 3, ' ');
            display(T->ptr[1], indent + 6); //显示变量列表
            break;
        case TYPE:
            printf("%*c类型： %s\n", indent, ' ', T->type_id);
            break;
        // case EXT_DEC_LIST:  display(T->ptr[0],indent);     //依次显示外部变量名，
        //                     display(T->ptr[1],indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
        //                     break;
        case EXT_DEC_LIST:
            if (T->ptr[0]->kind == ASSIGNOP)
            {
                display(T->ptr[0]->ptr[0], indent);
                printf("%*cASSIGNOP\n ", indent + 1, ' ');
                display(T->ptr[0]->ptr[1], indent);
            }
            else
            {
                display(T->ptr[0], indent);
            }
            display(T->ptr[1], indent); //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
            break;
        case FUNC_DEF:
            printf("%*c函数定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示函数返回类型
            display(T->ptr[1], indent + 3); //显示函数名和参数
            display(T->ptr[2], indent + 3); //显示函数体
            break;
        case ARRAY_DEF:
            printf("%*c数组定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            display(T->ptr[1], indent + 3);
            break;
        case FUNC_DEC:
            printf("%*c函数名：%s\n", indent, ' ', T->type_id);
            if (T->ptr[0])
            {
                printf("%*c函数形参：\n", indent, ' ');
                display(T->ptr[0], indent + 3); //显示函数参数列表
            }
            else
                printf("%*c无参函数\n", indent + 3, ' ');
            break;
        case ARRAY_DEC:
            printf("%*c%s%s\n", indent, ' ', "数组名：", T->type_id);
            printf("%*c%s\n", indent, ' ', "数组大小：");
            display(T->ptr[0], indent + 5);
            break;
        case PARAM_LIST:
            display(T->ptr[0], indent); //依次显示全部参数类型和名称，
            display(T->ptr[1], indent);
            break;
        case PARAM_DEC:
            printf("%*c类型：%s, 参数名：%s\n", indent, ' ', T->ptr[0]->type == INT ? "int" : "float", T->ptr[1]->type_id);
            break;
        case EXP_STMT:
            printf("%*c表达式语句：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            break;
        case RETURN:
            printf("%*c返回语句：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            break;
        case COMP_STM:
            printf("%*c复合语句：(%d)\n", indent, ' ', T->pos);
            printf("%*c复合语句的变量定义部分：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示定义部分
            printf("%*c复合语句的语句部分：\n", indent + 3, ' ');
            display(T->ptr[1], indent + 6); //显示语句部分
            break;
        case STM_LIST:
            display(T->ptr[0], indent); //显示第一条语句
            display(T->ptr[1], indent); //显示剩下语句
            break;
        case WHILE:
            printf("%*c循环语句：(%d)\n", indent, ' ', T->pos);
            printf("%*c循环条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示循环条件
            printf("%*c循环体：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示循环体
            break;
        case IF_THEN:
            printf("%*c条件语句(IF_THEN)：(%d)\n", indent, ' ', T->pos);
            printf("%*c条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示条件
            printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示if子句
            break;
        case IF_THEN_ELSE:
            printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n", indent, ' ', T->pos);
            printf("%*c条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示条件
            printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示if子句
            printf("%*cELSE子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[2], indent + 6); //显示else子句
            break;
        case DEF_LIST:
            display(T->ptr[0], indent); //显示该局部变量定义列表中的第一个
            display(T->ptr[1], indent); //显示其它局部变量定义
            break;
        case VAR_DEF:
            printf("%*c局部变量定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示变量类型
            display(T->ptr[1], indent + 3); //显示该定义的全部变量名
            break;
        case DEC_LIST:
            printf("%*c变量名：\n", indent, ' ');
            T0 = T;
            while (T0)
            {
                if (T0->ptr[0]->kind == ID)
                    printf("%*c %s\n", indent + 6, ' ', T0->ptr[0]->type_id);
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    printf("%*c %s ASSIGNOP\n ", indent + 6, ' ', T0->ptr[0]->ptr[0]->type_id);
                    display(T0->ptr[0]->ptr[1], indent + strlen(T0->ptr[0]->ptr[0]->type_id) + 7); //显示初始化表达式
                }
                T0 = T0->ptr[1];
            }
            break;
        case FOR:
            printf("%*cfor-循环：(%d)\n", indent, ' ', T->pos);
            printf("%*c循环表达式：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[0], indent + 5);
            printf("%*c循环体：\n", indent + 5, ' ');
            display(T->ptr[1], indent + 5);
            printf("%*c：\n", indent + 5, ' ');
            break;
        case FOR_LIST:
            printf("%*cfor-前续动作：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            printf("%*cfor-判断表达式：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[1], indent + 3);
            printf("%*cfor-后续动作：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[2], indent + 3);
            break;
        case PRE_CONDITION:
            display(T->ptr[0], indent);
            break;
        case ID:
            printf("%*cID： %s\n", indent, ' ', T->type_id);
            break;
        case INT:
            printf("%*cINT：%d\n", indent, ' ', T->type_int);
            break;
        case FLOAT:
            printf("%*cFLAOT：%f\n", indent, ' ', T->type_float);
            break;
        case CHAR:
            printf("%*cCHAR：%c\n", indent, ' ', T->type_char);
            break;
        case ASSIGNOP:
        case COMADD:
        case COMSUB:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            display(T->ptr[1], indent + 3);
            break;
        case NOT:
        case AUTOADD_L:
        case AUTOADD_R:
        case AUTOSUB_L:
        case AUTOSUB_R:
        case UMINUS:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            break;
        case FUNC_CALL:
            printf("%*c函数调用：(%d)\n", indent, ' ', T->pos);
            printf("%*c函数名：%s\n", indent + 3, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            break;
        case ARGS:
            i = 1;
            while (T)
            { //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
                struct ASTNode *T0 = T->ptr[0];
                printf("%*c第%d个实际参数表达式：\n", indent, ' ', i++);
                display(T0, indent + 3);
                T = T->ptr[1];
            }
            //                    printf("%*c第%d个实际参数表达式：\n",indent,' ',i);
            //                  display(T,indent+3);
            printf("\n");
            break;
        }
    }
}
void semantic_Analysis0(struct ASTNode *T)
{
}
int semantic_Analysis(struct ASTNode *T, int type, int level, char flag, int use)
{
    int index = 0;
    struct ASTNode *T0 = T;

    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            //ExtDef
            semantic_Analysis(T->ptr[0], type, level, flag, use); //显示该外部定义（外部变量和函数）列表中的第一个
            //ExtDefList
            semantic_Analysis(T->ptr[1], type, level, flag, use); //显示该外部定义列表中的其它外部定义
            break;
        case EXT_VAR_DEF:
            use = 0;
            //Specifier
            type = semantic_Analysis(T->ptr[0], type, level, flag, use);
            //ExtDecList
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case TYPE:
            return T->type;
        case EXT_DEC_LIST:
            // 下面的都是变量
            if (T->ptr[0]->kind == ASSIGNOP)
            {
                use = 0;
                flag = 'V';
                semantic_Analysis(T->ptr[0]->ptr[0], type, level, flag, use);
                use = 1;
                semantic_Analysis(T->ptr[0]->ptr[1], type, level, flag, use);
            }
            else
            {
                flag = 'V';
                semantic_Analysis(T->ptr[0], type, level, flag, use);

            }
            use = 0;
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case FUNC_DEF:
            //Specifier
            type = semantic_Analysis(T->ptr[0], type, level, flag, use);
            //FuncDec
            flag = 'F';
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            //CompSt
            semantic_Analysis(T->ptr[2], type, level, flag, use);
            break;
        case ARRAY_DEF:
            //Specifier
            type = semantic_Analysis(T->ptr[0], type, level, flag, use);
            flag = 'A';
            // ArrayDec
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case FUNC_DEC:
            //ID
            input_symbol(T,type,level,flag);
            // VarList
            var_count = 0;
            flag = 'P';
            semantic_Analysis(T->ptr[0], type, level + 1, flag, use);
            //回溯
            symtabs.symbols[symtabs.index - var_count - 1].paramnum = var_count;
            break;
        case ARRAY_DEC:
            //插入符号表
            input_symbol(T,type,level,flag);
            //Exp
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            break;
        case PARAM_LIST:
            //ParamDec
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case PARAM_DEC:
            var_count++;
            //Specifier
            type = semantic_Analysis(T->ptr[0], type, level, flag, use);
            use = 0;
            //VarDec
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case EXP_STMT:
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            break;
        case RETURN:
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            break;
        case COMP_STM:
            level++;
            flag = 'T';
            symbol_index.TX[symbol_index.top++] = symtabs.index;
            //DefList
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            //StmList
            semantic_Analysis(T->ptr[1], type, level, flag, use);

            display_symbol_table();
            symtabs.index = symbol_index.TX[--symbol_index.top];
            display_symbol_table();
            break;
        case STM_LIST:
            //stmt
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            // stmtlist
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case WHILE:
            //exp
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            // stmt
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case IF_THEN:
            // Exp
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            // Stmt
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case IF_THEN_ELSE:
            //Exp
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            // Stmt
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            // ELSE Stmt
            semantic_Analysis(T->ptr[2], type, level, flag, use);
            break;
        case DEF_LIST:
            //Def
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            // DefList
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case VAR_DEF:
            //Specifier
            type = semantic_Analysis(T->ptr[0], type, level, flag, use);
            //DecList
            flag = 'T';
            use = 0;
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case DEC_LIST:
            if (T->ptr[0]->kind == ASSIGNOP)
            {
                flag = 'T';
                semantic_Analysis(T->ptr[0]->ptr[0], type, level, flag, use);
                use = 1;
                semantic_Analysis(T->ptr[0]->ptr[1], type, level, flag, use);
            }
            else
            {
                flag = 'T';
                semantic_Analysis(T->ptr[0], type, level, flag, use);

            }
            use = 0;
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case FOR:
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        case FOR_LIST:
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            semantic_Analysis(T->ptr[2], type, level, flag, use);
            break;
        case PRE_CONDITION:
            use = 1;
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            break;
        case ID:
            index = 0;
            //定义变量
            if (use == 0)
            {
                input_symbol(T,type,level,flag);
            }
            else
            {
                //使用变量
                index = symtabs.index - 1;
                while (index >= 0)
                {
                    if (strcmp(symtabs.symbols[index].name, T->type_id) == 0 && (symtabs.symbols[index].flag == 'T' || symtabs.symbols[index].flag == 'V'))
                    {
                        return symtabs.symbols[index].type;
                    }
                    index--;
                }
                printf(" %s undeclared variable,line: %d\n", T->type_id, T->pos);
            }
            break;
        case INT:
            return INT;
        case FLOAT:
            return FLOAT;
        case CHAR:
            return CHAR;
        case ASSIGNOP:
        case COMADD:
        case COMSUB:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            use = 1;
            int type1 = semantic_Analysis(T->ptr[0], type, level, flag, use);
            int type2 = semantic_Analysis(T->ptr[1], type, level, flag, use);
            if(type1 == type2){
                return type1;
            }
            break;
        case NOT:
        case AUTOADD_L:
        case AUTOADD_R:
        case AUTOSUB_L:
        case AUTOSUB_R:
        case UMINUS:
            use = 1;
            return semantic_Analysis(T->ptr[0], type, level, flag, use);
        case FUNC_CALL:
            // 自上而下而下查找函数
            while (index < symtabs.index && symtabs.symbols[index].level == 0)
            {
                //查看是不是有函数定义
                if (strcmp(symtabs.symbols[index].name, T->type_id) == 0)
                {
                    if (symtabs.symbols[index].flag != 'F')
                    {
                        printf("ERROR！line: %d：%s is not a function\n", T->pos, T->type_id);
                    }
                    break;
                }
                index++;
            }
            //没有找到
            if (index == symtabs.index || symtabs.symbols[index].level != 0)
            {
                printf("ERROR！line: %d function %s undeclared \n", T->pos, T->type_id);
                break;
            }

            type = symtabs.symbols[index + 1].type;
            var_count = 0;
            //定义
            func_pos = index;
            semantic_Analysis(T->ptr[0], type, level, flag, use);
            if (symtabs.symbols[index].paramnum != var_count)
            {
                printf("ERROR! line: %d, %s function require %d param but get %d\n ", T->pos, symtabs.symbols[index].name, symtabs.symbols[index].paramnum, var_count);
            }
            break;
        case ARGS:
            use = 1;
            var_count++;
            int t = semantic_Analysis(T->ptr[0], type, level, flag, use);
            if (t != type)
            {
                printf("ERROR! line: %d function call %d th param not match\n", T->pos, var_count);
            }
            type = symtabs.symbols[func_pos + var_count + 1].type;
            semantic_Analysis(T->ptr[1], type, level, flag, use);
            break;
        }
    }
    return 0;

}

int getType(const char *type)
{
    if (!strcmp(type, "int"))
    {
        return INT;
    }
    else if (!strcmp(type, "float"))
    {
        return FLOAT;
    }
    else if (!strcmp(type, "char"))
    {
        return CHAR;
    }
    else
    {
        return 0;
    }
}