//
//  main.c
//  CTest
//
//  Created by luck-mac on 15/4/5.
//  Copyright (c) 2015年 com.nju. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define INPUT 0
#define OUTPUT 1
#define BUFFER_LEN 1024
int main(int argc, const char * argv[]) {
    pid_t pid;//进程号
    int file_descriptors[2];//文件描述符
    char buf[BUFFER_LEN];
    int return_count;//返回编号
    memset(buf, '\0', sizeof(buf));
    pipe(file_descriptors);
    if ((pid = fork())==-1) {
        printf("Fork 发生错误");
        return 1;
    }
    //子进程
    if (pid == 0) {
        FILE *pipeFile = popen("ls", "r");
        close(file_descriptors[INPUT]);
        fread(buf, sizeof(char), sizeof(buf), pipeFile);
        write(file_descriptors[OUTPUT], buf,strlen(buf));
        return 0;
    } else {
        //父进程
        wait(NULL);//阻塞，在子线程执行完后再执行父进程
        close(file_descriptors[OUTPUT]);
        return_count = read(file_descriptors[INPUT], buf, sizeof(buf));
        printf("%s", buf);
    }
    return 0;
}
