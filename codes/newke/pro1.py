# -*- coding:utf-8 -*-
class Solution:
    # array 二维列表
    def Find(self, target, array):
        if not isinstance(array, list):
            return False

        if not isinstance(array[0], list):
            return False

        rows = len(array)
        cols = len(array[0])
        row, col = 0, cols-1

        while True:            
            if row >= rows or col < 0:
                break

            value = array[row][col]
            if value == target:
                return True
            elif value > target:
                col -= 1
            else:
                row += 1

        return False



set nu                          "设置行号

set tabstop=4                   "设置tab键宽度
set expandtab                   "将tab转换为空格

set autoindent                  "自动缩进 take indent for new linefrom previous line
set noswapfile                  "禁止生成临时文件
 
set mouse=a                     "可以在buffer的任何地方使用鼠标

imap <C-e> <END>
imap <C-a> <HOME>
imap <C-u> <esc>d0i
imap <C-k> <esc>d$i

inoremap { {<CR>}<Esc>ka<CR><tab>
inoremap ( ()<left>
inoremap " ""<left>

map <C-a> ggVG

let g:neocomplcache_enable_at_startup = 1
let g:neocomplcache_enalbe_auto_select = 1


map <F5> :call CompileRunGcc()<CR>

func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec '!g++ % -o %<'
        exec '!time ./%<'
    elseif &filetype == 'c'
        exec '!g++ % -o %<'
        exec '!time ./%<'
    elseif &filetype == 'python'
        exec '!g++ % -o %<'
        exec '!time ./%<'

    endif
endfunc