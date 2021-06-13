# gdb-test-demo
gdb测试demo，包含断点、子进程、多进程、动态加载so库等

# 测试结论
gdb需要断点调试子进程，需要设置set follow-fork-mode child

无论父子进程动态加载库，都可直接增加断点调试


# vscode配置
### gdb调试配置见launch.json
	{
	    // Use IntelliSense to learn about possible attributes.
	    // Hover to view descriptions of existing attributes.
	    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
	    "version": "0.2.0",
	    "configurations": [
		{
		    "name": "(gdb) Launch",
		    "type": "cppdbg",
		    "request": "launch",
		    "program": "${workspaceFolder}/main",
		    "args": [],
		    "stopAtEntry": false,
		    "cwd": "${fileDirname}",
		    "environment": [],
		    "externalConsole": false,
		    "MIMode": "gdb",
		    "setupCommands": [
			{
			    "description": "Enable pretty-printing for gdb",
			    "text": "-enable-pretty-printing",
			    "ignoreFailures": true
			},
			{
			    "description": "Enable child debugger for gdb",
			    "text": "-gdb-set follow-fork-mode child",
			    "ignoreFailures": false
			}
		    ],
		    "sourceFileMap":{
			"/build/glibc-S9d2JN": "/usr/src/glibc" //需要下载glibc的源码文件，修改这里的配置
		    }
		}
	      ]
	}

### 编译指令见task.json文件


