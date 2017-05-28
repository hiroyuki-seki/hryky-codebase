nnoremap <C-k>q :bp<Bar>:bd<Space>#<CR>
nnoremap <C-k>w :w<Bar>:mksession!<CR>
nnoremap <C-k>y :execute "'a,.yank " . v:register<CR>
nnoremap <C-k>d :execute "'a,.delete " . v:register<CR>
nnoremap <F11> :cnext<BAR>:foldopen<CR>
nnoremap <F2> :tnext<BAR>:foldopen<CR>
nnoremap <S-F11> :cprevious<BAR>:foldopen<CR>
nnoremap <S-F2> :tprevious<BAR>:foldopen<CR>
nnoremap <Space> ma
