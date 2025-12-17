#include <stdio.h>
#include "word.h"

void read_text_file(const char *filename);
void save_binary(const char *fname);
void display_from_binary(const char *fname, int n);

int main() {
    char input[256];
    char binfile[] = "output.bin";
    int choice, n;

    init_groups();

    printf("Masukkan nama file input (txt): ");
    scanf("%255s", input);
    read_text_file(input);

    do {
        printf("\nMenu:\n");
        printf("1) Simpan ke file binari\n");
        printf("2) Tampilkan n kata\n");
        printf("3) Selesai\n");
        printf("Pilihan anda: ");
        scanf("%d", &choice);

        if (choice == 1) {
            save_binary(binfile);
        } else if (choice == 2) {
            if (!binary_saved) save_binary(binfile);
            do {
                printf("Masukkan n (1-25): ");
                scanf("%d", &n);
            } while (n <= 0 || n > 25);
            display_from_binary(binfile, n);
        }
    } while (choice != 3);

    printf("Program selesai.\n");
    return 0;
}
