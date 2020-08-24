#!build/cetushell
echo "Hello" World
echo '$PWD' "$PWD" $PWD
unset FOO
echo "$FOO"
FOO=BAR
echo $FOO
export FOO
env | grep FOO
echo FOO >&-
echo FOO >&- >&error
echo FOO |
grep -o OO
cat -e << EOF
hello
world '$PWD'
EOF
echo "double
quote
multi-
line"
echo '--------------------------------------------------'
cd /tmp
printf "Roses are red\nViolets blue\nAll my base\nI love you\n" | sort | cat -e > sorted_poem
sed -e 's/Roses/Turnips/' < sorted_poem > better_poem
cd -
echo "I prefer turnips anyway" >> /tmp/better_poem
cat /tmp/better_poem
echo '--------------------------------------------------'
ls notafile
foo
cd dfghdfgh
[ -e noperm ] || mkdir noperm
[ -x noperm ] && chmod 000 noperm
ls -la | grep noperm
cd noperm && echo "SHOULD HAVE PRINTED ERROR" || chmod 775 noperm
cd noperm; rm -rf ../noperm; cd ..; cd - && echo does not work as expected!
cd ~ && cd -
echo '--------------------------------------------------'
cat <<EOF
hoi dit is een heredoc
EOF
echo "foo\
 bar"
echo new\
line
echo comment #SHOULD BE IGNORED; ls -la; echo "OH NO
./cetushell <<EOF; echo $?
exit 42
EOF
jobs
hash -r
OLDPATH=$PATH
unset PATH
ls
vim
/bin/ls
export PATH=$OLDPATH
ls
ls       -l     -A
ls | sort | cat -e
echo '--------------------------------------------------'
testfile='/tmp/test.txt'
echo "Testing redirections," > $testfile; cat $testfile
echo "with multiple lines" >> $testfile; cat $testfile
wc -c < $testfile
testpoem='Roses are red
Violets are blue
All my base are belong to you
And so are you'
cat -e <<EOF
$testpoem
EOF
echo '--------------------------------------------------'
setshell --readonly READONLY=TRUE
unsetshell READONLY
unset READONLY
READONLY=FOO
setenv --readonly READONLY=EURT
unsetenv READONLY
unset READONLY
unsetenv --force READONLY
setenv READONLY=EURT
unset READONLY
env | grep READ
export READONLY
env | grep READ
unsetshell --force READONLY
unset READONLY
env
set
echo '--------------------------------------------------'
base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'
# sleep 5& jobs -p %?ep\ 5&& jobs
/sbin/pppd
/sbin/yubikey_shell
ls > /tmp/ftsh_ls_out /;cat /tmp/ftsh_ls_out
< /tmp/ftsh_ls_out cat -e >> /tmp/ftsh_ls_out
echo 1 >out >&2 2>err
echo 2 >out 2>err
cat err
cat out
ls -1; touch test_file; ls -1
# exit 1 | exit 2 | exit 3; echo "Stayin' Alive!"  #This test does not behave the same as eval sheet, but we specifically chose to copy zsh's behaviour here.
echo out >&-; echo out2 #out2
echo out >&- | echo out2 #out2
echo out >&- && echo out2 #no output, possibly error.
echo out >&- || echo out2 #out2
echo '--------------------------------------------------'
cat <<END
hello test
END
cat <<EO\
F
foo bar
EO\
F
EOF
cat > /tmp/heredoc_append << EOF
abc
EOF
cat -e >> /tmp/heredoc_append <<END
def
ghi
END
cat /tmp/heredoc_append
echo '--------------------------------------------------'
echo "echo abc; exit; echo def" | ./cetushell; echo $? # should only print 'abc' and exit code should be 0
echo "exit 999999999999999999999999999999999999999999" | ./cetushell; echo $? # should be consistent and not crash
echo "exit foo" | ./cetushell; echo $? #should print error about non-numerical argument, and exit code should be non-zero
echo "exit 42 2 3" | ./cetushell; echo $? #should print error about too many arguments, and return code should be non-zero. (don't exit!)
cd -L /tmp; cd -P .. #specific for MacOS
cd /tmp
type type ls # type is builtin, ls is command
echo '--------------------------------------------------'
ls doesnotexist || echo "OR operator works"; echo $?
echo 'No error' || echo 'You cant see me'; echo "${?}"
false && echo foo || echo bar #bar
false || echo foo && echo bar #foo
true || echo foo && echo bar #bar
true && echo foo || echo bar #foo
false && echo foo && echo oops || echo bar #bar
true || echo foo || echo oops && echo bar #bar

echo '--------------------------------------------------'
a=hello b=world; b=42 echo ${a}_${b} && echo ${b} #hello_word world
directory=/ ls_opt=-atr
ls ${ls_opt} ${directory} #ls -atr /
echo ${empty}|cat -e #only $
set | grep -E '(a|b)='#a=hello b=world
env | grep -E '(a|b)='#nothing (or LS_COLORS)
export b
printenv b #world
ONESHOT= env | grep ONESHOT
unset a b
set | grep -E '(a|b)='#nothing
env | grep -E '(a|b)='#nothing (or LS_COLORS)

echo '--------------------------------------------------'
unset PATH
PATH=/bin:/usr/bin
mkdir testdir
echo ${?} #0
ls -1 | grep testdir #testdir
rm -r testdir
echo '--------------------------------------------------'
true; echo ${?}; false; echo ${?} #0; 1
mkfifo fifo
ls -lR /usr/bin >fifo 2>&1 &
jobs
rm fifo
emacs -nw &
emacs -nw &
emacs -nw &
emacs -nw &
emacs -nw &
sleep 0.2
jobs #when in interactive mode, should show 5 suspended emacs. in non-interactive mode they will exit.
# in interactive mode, use fg to use the emacs'
echo "
Only 'ls -lR /usr/bin >fifo 2>&1 &' left:"
jobs
#in interactive mode, run 'ls -Rl / 2>&1' and press `ctrl-z`. then run jobs to show it is suspended.
exit 42
