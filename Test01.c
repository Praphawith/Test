#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 40
#define FIRSTNAME 30
#define SURNAME 30
#define PROFILE_PIC 300

typedef struct
{
    char nameTitle[8];
    char firstName[FIRSTNAME];
    char surName[SURNAME];
    char birthDate[11];
    int age;
    char profilePicture[PROFILE_PIC];
    time_t lastUpdated;
} Member;

Member members[MAX_MEMBERS];
int m_Count = 0;

void autoAge(Member *member)
{
    struct tm birth = {0};
    strtime(member->birthDate, "%Y - %m - %d", &birth);
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    member->age = current->tm_year + 1900 - birth.tm_year;
}

void addMember()
{
    if (m_Count >= MAX_MEMBERS)
    {
        printf("You can't add anymore member.\n");
        return;
    }

    Member newmember;
    printf("Enter Title (นาย, นาง, นางสาว): ");
    scanf("%s", newmember.nameTitle);
    printf("Enter first name: ");
    scanf("%s", newmember.firstName);
    printf("Enter last name: ");
    scanf("%s", newmember.surName);
    printf("Enter birth date (YYYY-MM-DD): ");
    scanf("%s", newmember.birthDate);
    printf("Enter profile picture path: ");
    scanf("%s", newmember.profilePicture);

    autoAge(&newmember);
    newmember.lastUpdated = time(NULL);

    members[m_Count++] = newmember;
    printf("Member added.\n");
}

void displayMembers()
{
    for (int i = 0; i < m_Count; i++)
    {
        printf("%s %s %s, Age: %d, Birth Date: %s, Last Updated: %s",
               members[i].nameTitle, members[i].firstName, members[i].surName,
               members[i].age, members[i].birthDate, ctime(&members[i].lastUpdated));
    }
}

void search()
{
    char searchName[FIRSTNAME];
    printf("Enter name or surname to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < m_Count; i++)
    {
        if (strcmp(members[i].firstName, searchName) == 0 || strcmp(members[i].surName, searchName) == 0)
        {
            printf("%s %s %s, Age: %d, Birth Date: %s\n",
                   members[i].nameTitle, members[i].firstName, members[i].surName,
                   members[i].age, members[i].birthDate);
        }
    }
}

void update()
{
    char searchName[FIRSTNAME];
    printf("Enter name or surname to update: ");
    scanf("%s", searchName);

    for (int i = 0; i < m_Count; i++)
    {
        if (strcmp(members[i].firstName, searchName) == 0 || strcmp(members[i].surName, searchName) == 0)
        {
            printf("Updating member: %s %s\n", members[i].firstName, members[i].surName);
            printf("Enter new birth date (YYYY-MM-DD): ");
            scanf("%s", members[i].birthDate);
            calculateAge(&members[i]);
            members[i].lastUpdated = time(NULL);
            printf("Member updated successfully.\n");
            return;
        }
    }
    printf("Member not found.\n");
}

void delete()
{
    char searchname[FIRSTNAME];
    printf("Enter name or surname to delete : ");
    scanf("%s", searchname);

    for (int i = 0; i < m_Count; i++)
    {
        if (strcmp(members[i].firstName, searchname) == 0 || strcmp(members[i].surName, searchname) == 0)
        {
            for (int j = i; j < m_Count - 1; j++)
            {
                members[j] = members[j + 1];
            }
            m_Count--;
            printf("Member deleted.\n");
            return;
        }
    }
    printf("not found.\n");
}

void displayStatistics()
{
}

int main()
{
    int choice;
    do
    {
        printf("\n1. Add Member\n2. Display Members\n3. Search Member\n4. Update Member\n5. Delete Member\n6. Display Statistics\n0. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMember();
            break;
        case 2:
            displayMembers();
            break;
        case 3:
            search();
            break;
        case 4:
            update();
            break;
        case 5:
            delete ();
            break;
        case 6:
            displayStatistics();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}