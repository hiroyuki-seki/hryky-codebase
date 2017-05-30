cnoremap <expr> <C-o>h expand('%:p:h')
cnoremap <expr> <C-o>p expand('%:p')
nnoremap <C-k><lt> :execute "'a,.<lt>"<CR>
nnoremap <C-k>> :execute "'a,.>"<CR>
nnoremap <C-k>C :execute 'normal! "' . v:register . "c`a"<BAR>:startinsert<CR>
nnoremap <C-k>D :execute "`a,.delete " . v:register<CR>
nnoremap <C-k>Y :execute "`a,.yank " . v:register<CR>
nnoremap <C-k>c :execute 'normal! "' . v:register . "c'a"<BAR>:startinsert<CR>
nnoremap <C-k>d :execute "'a,.delete " . v:register<CR>
nnoremap <C-k>q :bp<Bar>:bd<Space>#<CR>
nnoremap <C-k>w :w<Bar>:mksession!<CR>
nnoremap <C-k>y :execute "'a,.yank " . v:register<CR>
nnoremap <F11> :cnext<CR>
nnoremap <F2> :tnext<CR>
nnoremap <S-F11> :cprevious<CR>
nnoremap <S-F2> :tprevious<CR>
nnoremap <Space> ma
