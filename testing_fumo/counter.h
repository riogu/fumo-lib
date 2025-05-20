//! >>>>>>>>>>>>>>>> Counter >>>>>>>>>>>>>>>>
// clang-format off
#pragma region Counter

/* Counter
 * Ex:
 * <code>
CountOn(InitSteps);
int foo(void)
{
    CountIt();
    ...
    CountIt();
    ...
    CountIt();
    ...
}
Counted(InitSteps);
 * </code>
 * */
#define CountOn(name)               enum { name ## _BASE = __COUNTER__ }; const U8 name
#define CountIt(name)               (U8)(__COUNTER__ - (name ## _BASE))
#define Counted(name)               const U8 name = (U8)(__COUNTER__ - (name ## _BASE) -1);

/* alias of Counter
 * Ex:
 * <code>
TakeSteps(InitSteps);
int foo(void)
{
    AddStep();
    ...
    AddStep();
    ...
    AddStep();
    ...
}
TotalSteps(InitSteps);
 * </code>
 * */ 
// #define StrongAlias(TargetFunc, AliasDecl)  \
//   extern __typeof__ (TargetFunc) AliasDecl  \
//     __attribute__ ((alias (#TargetFunc), copy (TargetFunc)));
//
// extern __attribute__ ((alloc_size (1), malloc, nothrow)) void* allocate (size_t);
// StrongAlias (allocate, alloc);
//
// void func() {
//     StrongAlias(TargetFunc, AliasDecl)
// }



#define TakeSteps(name)             CountOn(name)
/* this is invalid to read, want to get value ? use 'CountIt(name)' OR 'NextStep(name)' */
#define AddStep()                   do { __COUNTER__; } while (0);
#define TotalSteps(name)            Counted(name)
/* better use of Counter (on format print 'step, total')
 * 'step' starts at 1
 * Ex:
 * <code>
TakeSteps(InitSteps);
int foo(void)
{
    printf(StepsPRT " Initializing system clock...", NextStep(InitSteps));
    ...
    printf(StepsPRT " Loading configurations...", NextStep(InitSteps));
    ...
    printf(StepsPRT " Applying...", NextStep(InitSteps));
    ...
}
TotalSteps(InitSteps);
 * </code>
 * */
#define NextStep(name)              CountIt(name), name
#define StepsPRT                    "%d of %d"
#define NextStepP                   StepsPRT

#pragma endregion Counter
//! <<<<<<<<<<<<<<<< .Counter <<<<<<<<<<<<<<<<
//

TakeSteps(InitSteps);
Counted(InitSteps);
NextStep(InitSteps);
AddStep();
TotalSteps(InitSteps);
