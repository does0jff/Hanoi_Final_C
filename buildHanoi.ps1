$root_dir = $args[0]
$DEBUG_FLAG = $args[1]

$bin_dir = "$root_dir\bin"
$src_dir = "$root_dir\src"
$inc_dir = "$root_dir\include"
$src_files = $(ls "$src_dir")
$DEBUG_STR = "-DDEBUG"

if ([System.IO.File]::Exists("$bin_dir\hanoi.exe")) 
{
    echo "Eliminando compilado anterior"
    rm "$bin_dir\hanoi.exe"
}

cd $src_dir
if($DEBUG_FLAG -eq "D")
{
    echo "Compilacion en modo Debug"
    gcc $src_files "$DEBUG_STR" "-I$inc_dir" -o "$bin_dir\hanoi.exe"
}
else
{
    echo "Compilacion normal"
    gcc $src_files "-I$inc_dir" -o "$bin_dir\hanoi.exe"
}
# gcc "$src_dir\hanoi.c" "$src_dir\game.c" "$src_dir\hanoi_disk.c" "$src_dir\hanoi_set.c" "$src_dir\stack.c" "-I$inc_dir" -o "$bin_dir\hanoi.exe"

ls "$bin_dir"
# cd $bin_dir
# .\hanoi.exe
cd ..
