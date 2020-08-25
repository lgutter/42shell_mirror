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
cd ~
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
setshell --help
setshell --readonly READONLY=TRUE
setenv --readonly 42SH=INVALID
setenv --readonly 42SHINVALID
unsetshell READONLY
unset READONLY
READONLY=FOO
setenv --readonly READONLY=EURT
setenv --readonly --force READONLY=EURT
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
unset --help
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
type env set hash true foo echo
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
set | grep -E '(a|b)=' #a=hello b=world
env | grep -E '(a|b)=' #nothing or LS_COLORS
shellenv
setshell
setenv
export b
printenv b #world
ONESHOT= env | grep ONESHOT
unset a b
set | grep -E '(a|b)='#nothing
env | grep -E '(a|b)='#nothing or LS_COLORS
a=hello b=world; b=42 echo ${a}_${b} && echo ${b} #hello_word world
export a c #no output expected
env | grep a #should show that a is hello
export -p
export -f #should print usage
echo '--------------------------------------------------'
OLDPATH=$PATH
unset PATH
export PATH=/bin:/usr/bin
mkdir testdir
echo ${?} #0
ls -1 | grep testdir #testdir
rm -r testdir
export PATH=$OLDPATH
echo '--------------------------------------------------'
true; echo ${?}; false; echo ${?} #0; 1
mkfifo fifo
ls -lR / >fifo 2>&1 &
jobs %1
rm fifo
emacs -nw &
emacs -nw &
emacs -nw &
emacs -nw &
emacs -nw &
sleep 0.5
jobs '%? ' #when in interactive mode, should show 5 suspended emacs. in non-interactive mode they will exit.
# in interactive mode, use fg to use the emacs'
echo "
Only 'ls -lR /usr/bin >fifo 2>&1 &' left:"
exit | cat -e #should not exit and print an error about unfinished jobs
jobs -l
bg %?foo #should print an error
bg %?fo #should print an error that job is in background
jobs -p
#in interactive mode, run 'ls -Rl / 2>&1' and press `ctrl-z`. then run jobs to show it is suspended.
echo '--------------------------------------------------'
echo 'foo\
bar' | cat -e
echo "foo\
bar" | cat -e
echo "'foo\
bar'
baz" | cat -e
l\
s \
-lat
echo abc \| cat -e
echo abc \\| cat -e
echo '--------------------------------------------------'
test
[ true ]
[ ]
[ error
echo '---------- -b BLOCK'
test -b /dev/disk0 && echo ok || echo wrong #ok WRONG IN CI
test -b /dev/console && echo ok || echo wrong #wrong
test -b DOESTNOTEXIST && echo ok || echo wrong #wrong
echo '---------- -c CHARACTER'
test -c /dev/disk0 && echo ok || echo wrong #wrong
test -c /dev/console && echo ok || echo wrong #ok
echo '---------- -d DIRECTORY'
test -d /dev/disk0 && echo ok || echo wrong #wrong
test -d ${HOME} && echo ok || echo wrong #ok
test -d /dev/disk0 && echo ok || echo wrong #wrong
test -d ${HOME} && echo ok || echo wrong #ok
echo '---------- -e EXISTS'
test -e /dev/null && echo ok || echo wrong #ok
test -e /usr/share/man/man2/execve.2 && echo ok || echo wrong #ok WRONG IN CI
test -e DOESTNOTEXIST && echo ok || echo wrong #wrong
echo '---------- -f FILE'
test -f /dev/null && echo ok || echo wrong #wrong
test -f /usr/share/man/man2/execve.2 && echo ok || echo wrong #ok WRONG IN CI
echo '---------- -L LINK'
test -L /dev/null && echo ok || echo wrong #wrong
test -L /var && echo ok || echo wrong #ok WRONG IN CI
test -h /dev/null && echo ok || echo wrong #wrong
test -h /var && echo ok || echo wrong #ok
echo '---------- -p FIFO'
cd /tmp
touch notfifo && mkfifo fifo
test -p fifo && echo ok || echo wrong #ok
test -p notfifo && echo ok || echo wrong #wrong
echo '---------- -r READ'
touch read noread; chmod u-r noread
test -r read && echo ok || echo wrong #ok
test -r noread && echo ok || echo wrong #wrong
echo '---------- -w WRITE'
touch write nowrite; chmod u-w nowrite
test -w write && echo ok || echo wrong #ok
test -w nowrite && echo ok || echo wrong #wrong
echo '---------- - EXEC'
touch exec noexec; chmod u+x exec
test -x exec && echo ok || echo wrong #ok
test -x noexec && echo ok || echo wrong #wrong
echo '---------- -S SOCKET'
# socketfile={{ Use one of the path output by "find /var/run -type s 2>/dev/null" }}
# test -S ${socketfile} && echo ok || echo wrong #ok
test -S /dev/null && echo ok || echo wrong #wrong
echo '---------- -s NON-ZERO FILE'
touch emptyfile; echo "not empty" > notempty
test -s emptyfile && echo ok || echo wrong #wrong
test -s notempty && echo ok || echo wrong #ok
echo '---------- SINGLE ARG'
a='hello' b=''; unset c
test ${a} && echo ok || echo wrong #ok
test ${b} && echo ok || echo wrong #wrong
test ${c} && echo ok || echo wrong #wrong
echo '---------- -z ZERO-LEN STR'
test -z ${a} && echo ok || echo wrong #wrong
test -z ${b} && echo ok || echo wrong #ok
test -z ${c} && echo ok || echo wrong #ok
echo '---------- -n NON-ZERO-LEN STR'
test -n ${a} && echo ok || echo wrong #ok
test -n ${b} && echo ok || echo wrong #wrong
test -n ${c} && echo ok || echo wrong #wrong
echo '---------- BINARY STR EXPR'
test 'abc' = 'def' && echo ok || echo wrong #wrong
test 'abc' = 'abc' && echo ok || echo wrong #ok
test 'abc' != 'def' && echo ok || echo wrong #ok
test 'abc' != 'abc' && echo ok || echo wrong #wrong
echo '---------- BINARY INT EXPR'
test 0 -eq 1 && echo ok || echo wrong #wrong
test -1 -eq 1 && echo ok || echo wrong #wrong
test -1 -eq -1 && echo ok || echo wrong #ok
first='12' second='34'
test ${first} -ne ${second} && echo ok || echo wrong #ok
test -1 -gt -2 && echo ok || echo wrong #ok
test 2 -ge 2 && echo ok || echo wrong #ok
test -2 -lt -2 && echo ok || echo wrong #wrong
test 3 -le +2 && echo ok || echo wrong #wrong
rm -rf tempdir; test ! -d tempdir && echo "tempdir removed" #tempdir removed
test zzz -eq 123 && echo ok || echo wrong # {{ Optionnal error message indicating integer expected }} wrong
echo '--------------------------------------------------'
hash mkdir; hash # {{ Print all hashes stored. One of them must be equivalent to: mkdir=/bin/mkdir }}
hash -r
hash
hash DOESNOTEXIST; hash # {{ Optionnal error message indicating that 'DOESNOTEXIST' command is not found }}
hash ps 42sh umount; hash # {{ Optionnal error message indicating that '42sh' command is not found }}
# {{ Print hashed path for "ps" and "umount" commands }}
echo '--------------------------------------------------'
cat <<EOF >segfault.c
#include <signal.h>
#include <unistd.h>

int main(void)
{
	kill(getpid(), SIGSEGV);
	return (0);
}
EOF
gcc segfault.c -o segfault && ./segfault #should print an error that command segfaulted
rm segfault
