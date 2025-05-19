// #include "fumo/optional_t.h"
// #include "fumo/variant.h"
// #include <stdbool.h>
// #include <stdio.h>
//
// void dict_add(dict d, char* key, int value) {
//     // snip
// }
//
// bool dict_has_key(dict d, char* key) {
//     // snip
// }
//
// optional_t dict_get(dict d, char* key) {
//     if (!dict_has_key(d, key)) return None();
//
//     return Some(d[key]);
// }
//
// optional_t get_input() {
//     int n;
//     if (scanf("%d", &n)) {
//         return Some(n);
//     }
//
//     return None();
// }
//
// int main() {
//     printf("How many fumo? (default: 727)");
//
//     let opt = get_input();
//
//     let result = match(opt) {
//         Some(value) value;
//         None() 727;
//     }
//
//     printf("You just obtained: %d fumo", result);
//
//     let mydict = dict();
//
//     dict_add(mydict, "fumo_count", result);
//
//     let fumo_count = 0;
//     Some(value) = get_if("fumo_count", mydict) {
//
//         printf("You indeed have %d fumo", value);
//         fumo_count = value;
//     }
//     else {
//         // a.get("fumo_count") returned None
//         printf("no fumo :(");
//         fumo_count = 0;
//     }
//
//     return 0;
// }
