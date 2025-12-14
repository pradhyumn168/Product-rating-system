#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Print stars
void printStars(int rating, char *stars) {
    if (rating > 5) rating = 5;
    for (int i = 0; i < rating; i++)
        stars[i] = '*';
    stars[rating] = '\0';
}

// Banner
void banner() {
    printf("\n");
    printf("==============================================================\n");
    printf("                    CUSTOMER FEEDBACK SYSTEM                  \n");
    printf("==============================================================\n");
}

// Check if feedback contains digits
int containsDigit(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (isdigit((unsigned char)str[i]))
            return 1;
    return 0;
}

int main() {
    FILE *fp;
    int s, brandChoice;

    // 📱 TOP 10 MOBILE BRANDS
    const char *brands[] = {
        "Samsung",
        "Apple",
        "Xiaomi",
        "Oppo",
        "Vivo",
        "Tecno",
        "Realme",
        "Motorola",
        "Honor",
        "Huawei"
    };

    int totalBrands = sizeof(brands) / sizeof(brands[0]);

    banner();

    // BRAND SELECTION
    printf("Select a Mobile Brand to Review:\n");
    for (int i = 0; i < totalBrands; i++) {
        printf("%d. %s\n", i + 1, brands[i]);
    }

    while (1) {
        printf("Enter your choice (1-%d): ", totalBrands);
        if (scanf("%d", &brandChoice) != 1 || brandChoice < 1 || brandChoice > totalBrands) {
            printf("Invalid input! Please select a valid brand.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        break;
    }

    const char *selectedBrand = brands[brandChoice - 1];
    printf("\nYou selected: *** %s ***\n", selectedBrand);

    printf("\nEnter number of customers giving feedback: ");
    scanf("%d", &s);
    getchar();

    fp = fopen("feedback.txt", "w");
    if (!fp) {
        printf("Error creating file!\n");
        return 1;
    }

    int r[s];
    char feedback[s][50];
    int total = 0;

    printf("\n========================= ENTER DETAILS ========================\n");

    for (int i = 0; i < s; i++) {

        // Feedback input
        while (1) {
            printf("\nCustomer %d Feedback for %s: ", i + 1, selectedBrand);
            scanf(" %49[^\n]", feedback[i]);

            if (containsDigit(feedback[i])) {
                printf("Invalid input! Feedback cannot contain numbers. Try again.\n");
                continue;
            }
            break;
        }

        // Rating input
        while (1) {
            printf("Customer %d Rating (1-5): ", i + 1);

            if (scanf("%d", &r[i]) != 1) {
                printf("Invalid input! Please enter a number between 1 and 5.\n");
                while (getchar() != '\n');
                continue;
            }

            if (r[i] < 1 || r[i] > 5) {
                printf("Invalid input! Rating must be between 1 and 5.\n");
                continue;
            }

            while (getchar() != '\n');
            break;
        }

        fprintf(fp, "%d|%s|%d|%s\n", i + 1, selectedBrand, r[i], feedback[i]);
        total += r[i];
    }

    fclose(fp);

    printf("\n====================== CUSTOMER FEEDBACKS ======================\n");
    printf("Brand Selected: %s\n\n", selectedBrand);

    printf("+-------------+----------+----------+---------------------------+\n");
    printf("| Customer No | Rating   | Stars    | Feedback                  |\n");
    printf("+-------------+----------+----------+---------------------------+\n");

    fp = fopen("feedback.txt", "r");
    int custNo, rating;
    char fb[50], brandName[30];
    char stars[10];

    while (fscanf(fp, "%d|%29[^|]|%d|%49[^\n]", &custNo, brandName, &rating, fb) == 4) {
        printStars(rating, stars);
        printf("| %-11d | %-8d | %-8s | %-25s |\n",
               custNo, rating, stars, fb);
    }
    fclose(fp);

    printf("+-------------+----------+----------+---------------------------+\n");

    printf("\n========================== SUMMARY =============================\n");

    float avg = (float) total / s;
    printf("Brand Reviewed: %s\n", selectedBrand);
    printf("Average Rating: %.1f\n", avg);

    if (avg >= 4.0)      printf("Overall Review: EXCELLENT\n");
    else if (avg >= 3.0) printf("Overall Review: GOOD\n");
    else if (avg >= 2.0) printf("Overall Review: AVERAGE\n");
    else                 printf("Overall Review: NEEDS IMPROVEMENT\n");

    printf("==============================================================\n");
    printf("                THANK YOU FOR USING THE SYSTEM!               \n");
    printf("==============================================================\n");

    return 0;
}