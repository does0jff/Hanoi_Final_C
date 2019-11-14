$root_dir = $args[0]

$bin_dir = "$root_dir\bin"
$src_dir = "$root_dir\src"
$inc_dir = "$root_dir\include"

gcc "$src_dir\hanoi.c" "$src_dir\game.c" "$src_dir\hanoi_disk.c" "$src_dir\hanoi_set.c" "$src_dir\stack.c" "-I$inc_dir" -o "$bin_dir\hanoi.exe"

ls "$bin_dir"
