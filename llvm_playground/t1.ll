declare i32 @puts(i8*)
declare i8* @gets(i8*)

@.str = private unnamed_addr constant [3 x i8] c"%s\00", align 1

define i32 @main() {
entry:
    %0 = alloca [1024 x i8], align 16
    %1 = getelementptr inbounds [1024 x i8], [1024 x i8]* %0, i64 0, i64 0
    %2 = call i8* @gets(i8* %1)
    %t1 = call i32 @puts(i8* %2)
    ret i32 0
}