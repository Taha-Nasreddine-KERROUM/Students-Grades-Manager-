#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stat
{
    double *grade;
    double avr;
};

void frstInstruction ( int *nstud, int *nsub )
{
    printf(" hola amigo, cuántos estudiantes tienes?: ");
    scanf("%d", nstud);
    printf(" Wie viele Fächer haben sie?: ");
    scanf("%d", nsub);
}

void secInstruction ( int **cof, int nsub )
{
    *cof = ( int* ) malloc ( nsub * sizeof(int) );
    printf("\n alright cute thin' enter the coefficients to these %d subjects:\n", nsub);
    for ( int *p = *cof; p < *cof + nsub; ++p ) {
        do {
            printf(" %ld", 1 + p - *cof);
            switch ( p - *cof ) {
                case 0:
                    printf("st");
                    break;
                case 1:
                    printf("nd");
                    break;
                case 2:
                    printf("rd");
                    break;
                default:
                    printf("th");
            }
            printf(" subject's coefficient: ");
            scanf("%d", p);
            if (*p > 5)
                printf(" %d? what are you, Harvard?\n re-enter:\n", *p);
            else if (*p < 1)
                printf(" how is that even possible nigga enter a real one\n again\n");
        } while ( (*p > 5) || (*p < 1) );
    }
}


void thirdInstruction ( struct stat **stud, int nstud, int nsub )
{
    *stud = ( struct stat* ) malloc ( nstud * sizeof( struct stat) );
    if ( *stud == NULL ) {
        printf(" students memory allocation failed");
        exit (1);
    }
    for ( struct stat *st = *stud; st < *stud + nstud; st++ ) {
        st -> grade = ( double* ) malloc ( nsub * sizeof( double ) );
        if ( st -> grade == NULL ) {
            printf(" one of the grades memory allocation failed");
            exit(1);
        }
    }
    for ( struct stat *st = *stud; st < *stud + nstud; st++ ) {
        printf("\n %ld", 1 + st - *stud );
            switch ( st - *stud ) {
                case 0:
                    printf("st");
                    break;
                case 1:
                    printf("nd");
                    break;
                case 2:
                    printf("rd");
                    break;
                default:
                    printf("th");
            }
        printf(" student grades:\n");
        for ( double *g = st -> grade; g < ( st -> grade ) + nsub; g++ ) {
            do {
                printf(" %ld", 1 + g - (st -> grade));
                switch ( st - *stud ) {
                    case 0:
                        printf("st");
                        break;
                    case 1:
                        printf("nd");
                        break;
                    case 2:
                        printf("rd");
                        break;
                    default:
                        printf("th");
                }
                printf(" subject's grade: ");
                scanf("%lf", g);
                if ( *g < 0 )
                    printf(" the heck is wrong with ya? put a real fuckin' mark\n re-enter the");
                else if ( *g > 20 )
                    printf(" who's this supposed to be? Einstein?\n re-enter a real");
            } while ( ( *g < 0 ) || ( *g > 20 ) );
        }
    }
}

void fourInstruction ( struct stat **stud, int *cof, int nstud, int nsub )
{
    int c = 0;
    for ( int *co = cof; co < cof + nsub; co++ )
        c += *co;
    for ( struct stat *st = *stud; st < *stud + nstud; st++ ) {
        st -> avr = 0;
        int *co = cof;
        for ( double *g = st -> grade; g < ( st -> grade ) + nsub; g++, co++ )
            st -> avr += *g * *co;
        st -> avr /= c;
    }
}

void fifInstruction ( struct stat *stud, int nstud, double *clasav, double *top )
{
    for ( struct stat *st = stud; st < stud + nstud; st++ )
        *clasav += st -> avr;
    *clasav /= nstud;
    for ( struct stat *st = stud; st < stud + nstud; st++ )
        if ( st -> avr > *clasav )
            (*top)++;
    *top *= 100.0 / nstud;
}

void drawBar ( int nsub, int len )
{
    printf("+");
    for ( int i = 0; i < nsub + 2; i++ ){
        for ( int j = 1; j <= len; j++ )
            printf("=");
        printf("+");
    }
    printf("\n");
}

void header( int nsub, int len )
{
    drawBar(nsub, len);
    printf("| %12s |", "students" );
    for ( int i = 0; i < nsub; ++i ) {
        char *ch = ( char* ) malloc ( len );
        switch ( i ) {
            case 0:
                sprintf(ch, " %dst subject", i + 1);
                break;
            case 1:
                sprintf(ch, " %dnd subject", i + 1);
                break;
            case 2:
                sprintf(ch, " %drd subject", i + 1);
                break;
            default:
                sprintf(ch, " %dth subject", i + 1);
        }
        printf(" %12s |", ch);
    }
    printf(" %12s |\n", "average" );
    drawBar(nsub, len);
}

void content ( int len, struct stat *stud, int nsub, int ns )
{
    
    char *ch = ( char* ) malloc ( len );
    int i;
    struct stat *st = stud + ns;
    double *g = st -> grade;
    switch ( ns ) {
        case 0:
            sprintf(ch, " %dst student", ns + 1);
            break;
        case 1:
            sprintf(ch, " %dnd student", ns + 1);
            break;
        case 2:
            sprintf(ch, " %drd student", ns + 1);
            break;
        default:
            sprintf(ch, " %dth student", ns + 1);
    }
    printf("| %12s |", ch);
    for ( i = 0; i < nsub; ++i, ++g )
        printf(" %12.2lf |", *g );
    printf(" %12.2lf |\n", st -> avr );
    drawBar(nsub, len);
}

int main()
{
    struct stat *student;
    int *coef, studnum, subnum, length = strlen(" 31st student ");
    double clavrg = 0, topkids = 0;
    frstInstruction ( &studnum, &subnum );
    secInstruction ( &coef, subnum );
    thirdInstruction ( &student, studnum, subnum );
    fourInstruction ( &student, coef, studnum, subnum );
    fifInstruction ( student, studnum, &clavrg, &topkids );
    printf("\n");
    header( subnum, length );
    for( int i = 0; i < studnum; ++i )
        content ( length, student, subnum, i );
        
    printf("\n the class average is %.2lf\n the percentage of kids up the average is %.2lf%%", clavrg, topkids);
        
    free ( coef );
    for ( struct stat *st = student; st < student + studnum; st++ ){
        free ( st -> grade );
        st -> grade = NULL;
    }
    free ( student );
    student = NULL;
    coef = NULL;
    return 0;
}
