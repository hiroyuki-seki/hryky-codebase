if exists('+colorcolumn')
	set colorcolumn=80
endif
set autoindent
set autowrite
set encoding=utf-8
set grepprg=grep\ -n\ --exclude=tags\ --exclude=TAGS\ --exclude=XTAGS
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
set number
set shellslash
set shiftwidth=4
set smartindent
set statusline=%n\ %f\ (%l\,%c)%y%m%r%{g:hryky.Statusline()}
set tabstop=4
set verbose=0
if has('win32')
	set guifontwide=MS_Gothic:h10
	set guifont=Lucida_Console:h10
	set ambiwidth=double
endif

