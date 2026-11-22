/* Pizza Pour Tous - phone order billing (simple version) */

#include <stdio.h>
#include <time.h>

#define GST_RATE 0.05
#define QST_RATE 0.09975

#define PRICE_3  20.49
#define PRICE_4  21.99
#define PRICE_8  24.49
#define PRICE_9  25.99
#define PRICE_13 28.49
#define PRICE_14 29.99

#define MAX_MEALS 20

int main(void)
{
    int choice;
    int invoiceNumber = 0;
    int totalMeals = 0;
    double totalSales = 0;

    char phone[30];
    char address[100];
    char payment;

    /* The meals of one order (the same position i = the same meal) */
    int mealNumbers[MAX_MEALS];
    char pizzaTypes[MAX_MEALS];
    int quantities[MAX_MEALS];
    int count;

    int mealNumber;
    char pizzaType;
    int quantity;
    char another;

    double price;
    double subtotal;
    double gst;
    double qst;
    double total;
    int i;
    time_t now;

    printf("Bienvenue chez Pizza Pour Tous!\n");
    printf("Ce programme facture les commandes telephoniques,\n");
    printf("et affiche le total des repas vendus et des ventes.\n");

    do
    {
        printf("\n1. Facturer une commande\n");
        printf("2. Afficher le total des repas vendus et des ventes\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        while (choice < 1 || choice > 3)
        {
            printf("Erreur : entrez 1, 2 ou 3.\n");
            printf("Votre choix : ");
            scanf("%d", &choice);
        }

        switch (choice)
        {
            case 1:
                printf("Numero de telephone du client : ");
                scanf(" %[^\n]", phone);
                printf("Adresse du client : ");
                scanf(" %[^\n]", address);

                count = 0;
                another = 'o';
                while (another == 'o' || another == 'O')
                {
                    /* Meal number */
                    printf("Numero du repas (3, 4, 8, 9, 13 ou 14) : ");
                    scanf("%d", &mealNumber);
                    while (mealNumber != 3 && mealNumber != 4 && mealNumber != 8 &&
                           mealNumber != 9 && mealNumber != 13 && mealNumber != 14)
                    {
                        printf("Erreur : numero de repas invalide.\n");
                        printf("Numero du repas (3, 4, 8, 9, 13 ou 14) : ");
                        scanf("%d", &mealNumber);
                    }

                    /* Pizza type */
                    printf("Type de pizza (v=vegetarienne, f=fromage, t=toute garnie, e=epinards, m=fruits de mer) : ");
                    scanf(" %c", &pizzaType);
                    while (pizzaType != 'v' && pizzaType != 'V' &&
                           pizzaType != 'f' && pizzaType != 'F' &&
                           pizzaType != 't' && pizzaType != 'T' &&
                           pizzaType != 'e' && pizzaType != 'E' &&
                           pizzaType != 'm' && pizzaType != 'M')
                    {
                        printf("Erreur : type de pizza invalide.\n");
                        printf("Type de pizza (v, f, t, e ou m) : ");
                        scanf(" %c", &pizzaType);
                    }

                    /* Quantity */
                    printf("Nombre de repas : ");
                    scanf("%d", &quantity);
                    while (quantity <= 0)
                    {
                        printf("Erreur : le nombre doit etre plus grand que 0.\n");
                        printf("Nombre de repas : ");
                        scanf("%d", &quantity);
                    }

                    /* Save this meal */
                    mealNumbers[count] = mealNumber;
                    pizzaTypes[count] = pizzaType;
                    quantities[count] = quantity;
                    count++;

                    /* Another meal? */
                    if (count == MAX_MEALS)
                    {
                        printf("Nombre maximum de repas atteint.\n");
                        another = 'n';
                    }
                    else
                    {
                        printf("Ajouter un autre repas ? (o/n) : ");
                        scanf(" %c", &another);
                        while (another != 'o' && another != 'O' &&
                               another != 'n' && another != 'N')
                        {
                            printf("Erreur : repondez par o ou n.\n");
                            printf("Ajouter un autre repas ? (o/n) : ");
                            scanf(" %c", &another);
                        }
                    }
                }

                /* Payment method */
                printf("Mode de paiement (C=Comptant, D=Debit, R=Credit) : ");
                scanf(" %c", &payment);
                while (payment != 'C' && payment != 'c' &&
                       payment != 'D' && payment != 'd' &&
                       payment != 'R' && payment != 'r')
                {
                    printf("Erreur : mode de paiement invalide.\n");
                    printf("Mode de paiement (C, D ou R) : ");
                    scanf(" %c", &payment);
                }

                /* Invoice header */
                invoiceNumber++;
                now = time(NULL);
                printf("\n==================================================\n");
                printf("Pizza Pour Tous\n");
                printf("Garage Keyce Titi\n");
                printf("Tel. : +237 620 239 480\n");
                printf("==================================================\n");
                printf("Facture no : %d\n", invoiceNumber);
                printf("Date et heure : %s", ctime(&now));
                printf("Adresse du client : %s\n", address);
                printf("Telephone du client : %s\n", phone);
                printf("--------------------------------------------------\n");

                /* Meals: print each line and add up the subtotal */
                subtotal = 0;
                for (i = 0; i < count; i++)
                {
                    if (mealNumbers[i] == 3)
                    {
                        price = PRICE_3;
                        printf("1 Pizza moyenne 12\" + 1 petit shawarma + 1 Pepsi (355 ml)\n");
                    }
                    else if (mealNumbers[i] == 4)
                    {
                        price = PRICE_4;
                        printf("1 Pizza moyenne 12\" + 10 ailes de poulet + frites + 1 Pepsi (355 ml)\n");
                    }
                    else if (mealNumbers[i] == 8)
                    {
                        price = PRICE_8;
                        printf("1 Grande pizza 14\" + 1 shawarma moyen + 1 Pepsi (355 ml)\n");
                    }
                    else if (mealNumbers[i] == 9)
                    {
                        price = PRICE_9;
                        printf("1 Grande pizza 14\" + 12 ailes de poulet + frites + 1 Pepsi (355 ml)\n");
                    }
                    else if (mealNumbers[i] == 13)
                    {
                        price = PRICE_13;
                        printf("1 Pizza extra-large 16\" + 1 grand shawarma + 1 Pepsi (355 ml)\n");
                    }
                    else
                    {
                        price = PRICE_14;
                        printf("1 Pizza extra-large 16\" + 15 ailes de poulet + 1 Pepsi (355 ml)\n");
                    }

                    if (pizzaTypes[i] == 'v' || pizzaTypes[i] == 'V')
                    {
                        printf("   Pizza : Vegetarienne\n");
                    }
                    else if (pizzaTypes[i] == 'f' || pizzaTypes[i] == 'F')
                    {
                        printf("   Pizza : Fromage\n");
                    }
                    else if (pizzaTypes[i] == 't' || pizzaTypes[i] == 'T')
                    {
                        printf("   Pizza : Toute garnie\n");
                    }
                    else if (pizzaTypes[i] == 'e' || pizzaTypes[i] == 'E')
                    {
                        printf("   Pizza : Epinards\n");
                    }
                    else
                    {
                        printf("   Pizza : Fruits de mer\n");
                    }

                    printf("   %d x %.2f $ = %.2f $\n", quantities[i], price, price * quantities[i]);
                    subtotal = subtotal + price * quantities[i];
                    totalMeals = totalMeals + quantities[i];
                }

                /* Taxes and total */
                gst = subtotal * GST_RATE;
                qst = subtotal * QST_RATE;
                total = subtotal + gst + qst;
                totalSales = totalSales + total;

                printf("--------------------------------------------------\n");
                printf("Sous-total     : %10.2f $\n", subtotal);
                printf("TPS (5%%)       : %10.2f $\n", gst);
                printf("TVQ (9.975%%)   : %10.2f $\n", qst);
                printf("TOTAL          : %10.2f $\n", total);

                if (payment == 'C' || payment == 'c')
                {
                    printf("Paiement : Comptant\n");
                }
                else if (payment == 'D' || payment == 'd')
                {
                    printf("Paiement : Debit\n");
                }
                else
                {
                    printf("Paiement : Credit\n");
                }
                printf("==================================================\n");
                printf("Merci de votre commande chez Pizza Pour Tous!\n");
                break;

            case 2:
                now = time(NULL);
                printf("\n==================================================\n");
                printf("Pizza Pour Tous\n");
                printf("Tel. : +237 620 239 480\n");
                printf("Adresse : Garage Keyce Titi\n");
                printf("Date et heure : %s", ctime(&now));
                printf("Nombre total de repas vendus : %d\n", totalMeals);
                printf("Montant total des ventes     : %.2f $\n", totalSales);
                printf("==================================================\n");
                break;

            case 3:
                printf("Merci et à la prochaine\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
