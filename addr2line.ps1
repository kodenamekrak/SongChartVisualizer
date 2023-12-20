param($p1, $p2)

if ($p1 -and $p2)
{
    & C:\android-ndk-r26b\toolchains\llvm\prebuilt\windows-x86_64\bin\llvm-addr2line.exe -e .\build\debug\$p1 $p2
}
else
{
	echo give at least 1 argument
}
