int a = 10, b ,c;
int g[10];
char d,f = 'f';
// int a[10];//目前只支持一维数组支持
float m,n;

int fibo(int a){
    if(a == 1|| a==2){
        return 1;
    }
    return fibo(a-1)+fibo(a-2);
}
//this is  annotation  
/*aaa*/
int main() {
    int m = 0,n,i;
    char d;
    // int a[10];
    m = read();
    i = 1;
    i += 1; 
    d = 'a';
    i++;
    ++i;
    i--;
    // g[1] = 10;
    while (i<= m)
    {
        n = fibo(i);
        write(n);
        i = i+1;
    }
    //for循环支持
    // for(i = 0;i<8;i++){
    //     i++;
    // }
    i++;
    return 1;
}
