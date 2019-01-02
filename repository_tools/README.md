# repository_tools
Make code management easy

Like Google depot_tools 用来管理代码的工具  
#### 初版开发背景:
因为我们工程是多个branch，每次都要单个目录去更新，自己感觉麻烦就写了个简单脚本  

#### 使用方法:
首先要保证git 和 python设置到环境变量中，也就是要在命令行中可以用，因为要用脚本去执行  
把工程下载后放到需要更新的目录一级上(同级别)然后执行里面的pull脚本，正确的话就没有什么提示的，错误有提示。

#### 核心Code
```py
def main(args = None):
  for folder in os.listdir(SCRIPT_PATH):
    folder = os.path.join(SCRIPT_PATH, folder)
    for git_folder in os.listdir(folder):
      if git_folder == '.git':
        os.chdir(folder)
        git.run('fetch', '-p')
        cur_branch = git.current_branch()
        git.run('rebase', 'origin/master', cur_branch)
        break
```

#### 后续
后面如果有需要可以继续添加更多脚本
