if exists('+colorcolumn')
	set colorcolumn=80
endif
set autoindent
set autowrite
set cursorcolumn
set cursorline
set encoding=utf-8
set foldmethod=manual
set grepprg=grep\ -n\ -R
set grepprg+=\ --include=*.h
set grepprg+=\ --include=*.c
set grepprg+=\ --include=*.cpp
set grepprg+=\ --include=*.m
set grepprg+=\ --include=*.mm
set grepprg+=\ --exclude=tags
set grepprg+=\ --exclude=TAGS
set grepprg+=\ --exclude=XTAGS
set grepprg+=\ --exclude=*.tmp
set grepprg+=\ --exclude=*.bak
set grepprg+=\ --exclude=\\#*\\#
set guioptions-=L
set guioptions-=R
set guioptions-=T
set guioptions-=b
set guioptions-=l
set guioptions-=m
set guioptions-=r
set hlsearch
set iminsert=0 "disables Input Method in Insert mode.
set imsearch=0 "disables Input Method when entering a search parttern.
set list
set listchars=tab:¬¬,trail:«
set noexpandtab
set nowrapscan
set number
set shellslash
set shiftwidth=4
set smartindent
set statusline=%n\ %f\ (%l\,%v)%y%m%r%{g:my.Statusline()}
set tabstop=4
set verbose=0
if has('win32')
	set guifontwide=MS_Gothic:h10
	set guifont=Lucida_Console:h10
	set ambiwidth=double
endif
if has('path_extra')
	set tags=./tags;,tags
endif

