#include <stdio.h>

int main(void)
{
    {
        // Array of int
        int nums[] = { 1, 2, 3, 4, 5 };
        printf("nums     - address:%p sizeof(nums):%d == sizeof(int) * length\n", nums, sizeof(nums));
        printf("&nums[0] - address:%p sizeof(&nums[0]):%d == sizoeof(int*)\n", &nums[0], sizeof(&nums[0]));
        int len = sizeof(nums) / sizeof(int);
        int i = 0;
        puts("nums[i]");
        for (i = 0; i < len; i++) {
            printf("%p %d\n", &nums[i], nums[i]);
        }
        puts("(&nums[0])[i] - nums is syntax sugar for &nums[0]");
        for (i = 0; i < len; i++) {
            printf("%p %d\n", &((&nums[0])[i]), (&nums[0])[i]);
        }
        puts("*(&nums[0] + i) - p[i] is syntax sugar for *(p + i)");
        for (i = 0; i < len; i++) {
            printf("%p %d\n", &nums[0] + i, *(&nums[0] + i));
        }
        puts("*(nums + i)");
        for (i = 0; i < len; i++) {
            printf("%p %d\n", nums + i, *(nums + i));
        }
    }

    {
        // Array of char
        char chrs[] = "deadbeef";
        // char chrs[] = { 'd', 'e', 'a', 'd', 'b', 'e', 'e', 'f', '\0' };

        // String literal
        char* chrp = "deadbeef";
        // const char* chrp = "deadbeef"; // should add const modifier.

        int len = sizeof(chrs) / sizeof(char);
        int i = 0;

        printf("chrs     - address:%p sizeof(chrs):%d == sizeof(char) * (length + nil)\n", chrs, sizeof(chrs));
        printf("&chrs[0] - address:%p sizeof(&chrs[0]):%d == sizoeof(char*)\n", &chrs[0], sizeof(&chrs[0]));
        for (i = 0; i < len; i++) {
            printf("chrs[%d]     - %p %c\n", i, &chrs[i], chrs[i]);
            printf("*(chrs + %d) - %p %c\n", i, chrs + i, *(chrs + i));
        }
        chrs[4] = '\0';
        printf("%s\n", chrs);

        printf("chrp     - address:%p sizeof(chrp):%d = sizeof(char*)\n", chrp, chrp, sizeof(chrp));
        printf("&chrp[0] - address:%p sizeof(&chrp[0]):%d = sizeof(char*)\n", &chrp[0], &chrp[0], sizeof(&chrp[0]));
        for (i = 0; i < len; i++) {
            printf("chrp[%d]     - %p %c\n", i, &chrp[i], chrp[i]);
            printf("*(chrp + %d) - %p %c\n", i, chrp + i, *(chrp + i));
        }
#if 0
        // String literal is not immutable, might cause segmentation fault.
        chrp[4] = '\0';
        printf("%s\n", chrp);
#endif
    }

    {
        // Structure
        typedef struct {
            char name[256];
            int age;
        } person;

        person psn = { "Foo", 23 };
        person* psnp = &psn;
        printf("psn.     - name:%s age:%d\n", psn.name, psn.age);
        printf("*(psnp). - name:%s age:%d\n", (*psnp).name, (*psnp).age);
        printf("psnp->   - name:%s age:%d\n", psnp->name, psnp->age);

        person people[3];
        printf("people - address:%p sizeof(people):%d == sizeof(person) * length\n", people, sizeof(people));
        int len = 3;
        int i;
        for (i = 0; i < len; i++) {
            sprintf(people[i].name, "Name%d", i + 1);
            people[i].age = 20 + i;
        }
        for (i = 0; i < len; i++) {
            printf("people[%d].name %p %s\n", i, &people[i].name, people[i].name);
            printf("people[%d].age  %p %d\n", i, &people[i].age, people[i].age);
        }
        for (i = 0; i < len; i++) {
            printf("(*(people + %d)).name %p %s\n", i, &((*(people + i)).name), (*(people + i)).name);
            printf("(*(people + %d)).age  %p %d\n", i, &((*(people + i)).age), (*(people + i)).age);
        }
        for (i = 0; i < len; i++) {
            printf("(people + %d)->name %p %s\n", i, &((people + i)->name), (people + i)->name);
            printf("(people + %d)->age  %p %d\n", i, &((people + i)->age), (people + i)->age);
        }
    }
}
