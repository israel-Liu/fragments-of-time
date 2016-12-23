# fragments-of-time

#### Coding Style
```CPP
namespace hinata {      // 命名空间左大括号在同一行，并留一个空号
                        // 一般这里留个空行
template <typename T>   // 模板声明 提前4个空格 TAB == 4 空格，不使用TAB
    class coding_style
    {                   // 类名左大括号，放到新行，放到类声明同一行感觉不好看
    public:
        coding_style()
            : cnt_(new std::size_t(1))
        {}              // 函数空大括号在新一行，并且中间不留有空格

        coding_style(const coding_style& rc)
            : cnt_(rc.cnt_),
              line_(0) // 初始化列表放到类声明下一行,如果变量比较多逗号放后面
        {
            ++*cnt_;
        }

        ~coding_style()
        {
            if (--*cnt_ == 0) {
                delete cnt_;
            }         // 控制语句，左大括号放到控制语句同一行，并留有空格
        }

        // modifiers // 单行注释后面留有空格
        void swap(coding_style& rhs,
                  arg arg_1,
                  arg arg_2)
        {            
                     // 当有多个参数的时候，折行和左小括号对齐
        }

    private:          
        int           line_;
        std::size_t*  cnt_ = nullptr;  
                      // 成员变量使用后下划线风格
    };
                      // 还有一堆需要添加空格的地方
} // namesapce hinata
```
最怕你一生碌碌无为，却安慰自己平凡可贵。
