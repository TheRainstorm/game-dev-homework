# 编译

## 1. VisualStudio

1. 把include/添加到项目propreties里的Additional Include Directories

2. 由于Windows下默认没有pthread线程库，因此需要自己下载。

   下载地址： https://sourceware.org/pthreads-win32/ 

   本项目已经包含了x64版本的.lib和.dll以及头文件pthread/。

3. 把pthread/添加到Additional Include Directories

4. 把当前文件夹pthreadVC2.lib所在文件夹添加到Linker->General>Additional Library Directories

5. 把pthreadVC2.lib添加到Linker->Input->Additional Dependencies

6. **(important)**在C/C++->Preprocessor->PreprocessorDefinitions添加HAVE_STRUCT_TIMESPEC

## 2. MinGW

- 支持ANSI Escape codes

  ```bash
  mingw32-make.exe
  ```

- 不支持时

  ```bash
  #修改src/draw.cpp顶部宏定义为
  #define NO_SUPPORT_ESCAPE_CODE
  
  mingw32-make.exe cscrutil
  ```

## 3. Linux

移植情况:

采用termios.h实现了类似于conio.h的getch(). [stackoverflow ](https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux )

编译：

```bash
make
```

