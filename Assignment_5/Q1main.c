#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 3
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}
int HashInsert(int key, HashSlot hashTable[])
{
    int comp=0;
    if (hashTable == NULL) return -1;
    int index = hash1(key);
    int step = hash2(key);
    int key_comp=0;
    int deleted_slot = -1;


    while (hashTable[index].indicator == USED)
    {
        if (hashTable[index].key == key) return -1;
        key_comp++;
        index = (index + step) % TABLESIZE;

        if (key_comp >= TABLESIZE) return TABLESIZE;

    }

    if(hashTable[index].indicator == DELETED)
    {
        deleted_slot = index;

        while(hashTable[index].indicator != EMPTY  && key_comp < TABLESIZE)
        {
            if (hashTable[index].indicator == USED)
            {
                if (hashTable[index].key == key)
                {
                    return -1;
                }
                key_comp++;
            }

            index = (index + step) % TABLESIZE;
        }

        hashTable[deleted_slot].key = key;
        hashTable[deleted_slot].indicator = USED;
        return key_comp;
    }


    hashTable[index].key = key;
    hashTable[index].indicator = USED;
    return key_comp;


}
int HashDelete(int key, HashSlot hashTable[])
{
    int comp = 0;
    if (hashTable == NULL) return -1;
    int index = hash1(key);
    int step = hash2(key);

    while (comp < TABLESIZE && hashTable[index].indicator != EMPTY){
        if (hashTable[index].indicator == USED && hashTable[index].key == key){
            hashTable[index].indicator = DELETED;
            return comp;
        }
        index = (index + step) % TABLESIZE;
        comp++;
    }
    if (hashTable[index].indicator == DELETED || hashTable[index].indicator == EMPTY) return -1;
    return -1;

}

