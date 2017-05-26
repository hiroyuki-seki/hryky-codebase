nnoremap <C-k>q :bp<Bar>:bd<Space>#<CR>
nnoremap <C-k>w :w<Bar>:mksession!<CR>
nnoremap <C-k>y :execute "'a,.yank " . v:register<CR>
nnoremap <C-k>d :execute "'a,.delete " . v:register<CR>
nnoremap <F11> :cnext<CR>
nnoremap <F8> :tnext<CR>
nnoremap <S-F11> :cprevious<CR>
nnoremap <S-F8> :tprevious<CR>
nnoremap <Space> ma
