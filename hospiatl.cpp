#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 200
#define MAX_DOCTORS 100
#define MAX_APPOINTMENTS 300

// ---------------- STRUCTURES ----------------
struct Patient {
    int id;
    char name[50];
    int age;
};

struct Doctor {
    int id;
    char name[50];
    char speciality[50];
};

struct Appointment {
    int patientId;
    int doctorId;
    char date[20];
};

struct Ambulance {
    int id;
    char driverName[50];
    char phone[15];
};

// ---------------- FUNCTION DECLARATIONS ----------------
// Patient
void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();
void editPatient();
void sortPatientsAZ();
void patientStats();

// Doctor
void addDoctor();
void viewDoctors();
void searchDoctor();
void deleteDoctor();
void editDoctor();
void sortDoctorsAZ();
void doctorStats();

// Appointment
void addAppointment();
void viewAppointments();
void deleteAppointment();

// Ambulance
void addAmbulance();
void viewAmbulance();

// Billing
void generateBill();

// ---------------- MAIN MENU ----------------
int main() {
    int choice;

    while (1) {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n2. View Patients\n3. Search Patient\n4. Delete Patient\n5. Edit Patient\n6. Sort Patients A-Z\n7. Patient Statistics\n");
        printf("8. Add Doctor\n9. View Doctors\n10. Search Doctor\n11. Delete Doctor\n12. Edit Doctor\n13. Sort Doctors A-Z\n14. Doctor Statistics\n");
        printf("15. Make Appointment\n16. View Appointments\n17. Delete Appointment\n");
        printf("18. Ambulance Service\n19. Billing\n0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: editPatient(); break;
            case 6: sortPatientsAZ(); break;
            case 7: patientStats(); break;

            case 8: addDoctor(); break;
            case 9: viewDoctors(); break;
            case 10: searchDoctor(); break;
            case 11: deleteDoctor(); break;
            case 12: editDoctor(); break;
            case 13: sortDoctorsAZ(); break;
            case 14: doctorStats(); break;

            case 15: addAppointment(); break;
            case 16: viewAppointments(); break;
            case 17: deleteAppointment(); break;

            case 18:
                printf("\n1. Add Ambulance\n2. View Ambulance\nChoose: ");
                int aChoice;
                scanf("%d", &aChoice);
                if(aChoice == 1) addAmbulance();
                else if(aChoice == 2) viewAmbulance();
                else printf("Invalid choice!\n");
                break;

            case 19: generateBill(); break;
            case 0: return 0;
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////
//                   PATIENT FUNCTIONS
/////////////////////////////////////////////////////////
void addPatient() {
    FILE *fp = fopen("patients.txt", "a");
    struct Patient p;

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    fprintf(fp, "%d %s %d\n", p.id, p.name, p.age);
    fclose(fp);

    printf("Patient added successfully!\n");
}

void viewPatients() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient p;

    printf("\n---- Patient List ----\n");
    while (fscanf(fp, "%d %s %d", &p.id, p.name, &p.age) != EOF) {
        printf("ID: %d  Name: %s  Age: %d\n", p.id, p.name, p.age);
    }
    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient p;
    int id, found = 0;

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &p.id, p.name, &p.age) != EOF) {
        if (p.id == id) {
            printf("\nPatient Found!\nID: %d  Name: %s  Age: %d\n", p.id, p.name, p.age);
            found = 1;
            break;
        }
    }

    if (!found) printf("Patient not found!\n");
    fclose(fp);
}

void deletePatient() {
    FILE *fp = fopen("patients.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    struct Patient p;
    int id;

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &p.id, p.name, &p.age) != EOF) {
        if (p.id != id) fprintf(tmp, "%d %s %d\n", p.id, p.name, p.age);
    }

    fclose(fp); fclose(tmp);
    remove("patients.txt");
    rename("temp.txt", "patients.txt");
    printf("Patient deleted successfully!\n");
}

void editPatient() {
    FILE *fp = fopen("patients.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    struct Patient p;
    int id, found = 0;

    printf("Enter Patient ID to edit: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &p.id, p.name, &p.age) != EOF) {
        if (p.id == id) {
            found = 1;
            printf("Enter NEW Name: ");
            scanf(" %[^\n]", p.name);
            printf("Enter NEW Age: ");
            scanf("%d", &p.age);
        }
        fprintf(tmp, "%d %s %d\n", p.id, p.name, p.age);
    }

    fclose(fp); fclose(tmp);
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf("Patient updated successfully!\n");
    else printf("Patient not found!\n");
}

void sortPatientsAZ() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient arr[MAX_PATIENTS], temp;
    int count = 0;

    while(fscanf(fp, "%d %s %d", &arr[count].id, arr[count].name, &arr[count].age) != EOF) count++;
    fclose(fp);

    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(strcmp(arr[i].name, arr[j].name) > 0){
                temp = arr[i]; arr[i]=arr[j]; arr[j]=temp;
            }
        }
    }

    printf("\n---- Patients A-Z ----\n");
    for(int i=0;i<count;i++) printf("ID: %d  Name: %s  Age: %d\n", arr[i].id, arr[i].name, arr[i].age);
}

void patientStats() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient p;
    int count=0, ageSum=0;
    while(fscanf(fp,"%d %s %d",&p.id,p.name,&p.age)!=EOF){
        count++;
        ageSum+=p.age;
    }
    fclose(fp);
    if(count==0) { printf("No patients.\n"); return; }
    printf("Total Patients: %d\nAverage Age: %.2f\n", count, (float)ageSum/count);
}

/////////////////////////////////////////////////////////
//                    DOCTOR FUNCTIONS
/////////////////////////////////////////////////////////
void addDoctor() {
    FILE *fp = fopen("doctors.txt", "a");
    struct Doctor d;

    printf("Enter Doctor ID: ");
    scanf("%d", &d.id);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", d.name);
    printf("Enter Speciality: ");
    scanf(" %[^\n]", d.speciality);

    fprintf(fp, "%d %s %s\n", d.id, d.name, d.speciality);
    fclose(fp);

    printf("Doctor added successfully!\n");
}

void viewDoctors() {
    FILE *fp = fopen("doctors.txt", "r");
    struct Doctor d;
    printf("\n---- Doctor List ----\n");
    while(fscanf(fp, "%d %s %s",&d.id,d.name,d.speciality)!=EOF){
        printf("ID: %d  Name: %s  Speciality: %s\n",d.id,d.name,d.speciality);
    }
    fclose(fp);
}

void searchDoctor() {
    FILE *fp = fopen("doctors.txt", "r");
    struct Doctor d;
    int id, found=0;
    printf("Enter Doctor ID to search: "); scanf("%d",&id);
    while(fscanf(fp,"%d %s %s",&d.id,d.name,d.speciality)!=EOF){
        if(d.id==id){ found=1; printf("\nDoctor Found!\nID:%d Name:%s Speciality:%s\n",d.id,d.name,d.speciality); break;}
    }
    if(!found) printf("Doctor not found!\n");
    fclose(fp);
}

void deleteDoctor() {
    FILE *fp=fopen("doctors.txt","r");
    FILE *tmp=fopen("temp.txt","w");
    struct Doctor d; int id;
    printf("Enter Doctor ID to delete: "); scanf("%d",&id);
    while(fscanf(fp,"%d %s %s",&d.id,d.name,d.speciality)!=EOF){
        if(d.id!=id) fprintf(tmp,"%d %s %s\n",d.id,d.name,d.speciality);
    }
    fclose(fp); fclose(tmp);
    remove("doctors.txt"); rename("temp.txt","doctors.txt");
    printf("Doctor deleted successfully!\n");
}

void editDoctor() {
    FILE *fp=fopen("doctors.txt","r");
    FILE *tmp=fopen("temp.txt","w");
    struct Doctor d; int id,found=0;
    printf("Enter Doctor ID to edit: "); scanf("%d",&id);
    while(fscanf(fp,"%d %s %s",&d.id,d.name,d.speciality)!=EOF){
        if(d.id==id){
            found=1;
            printf("Enter NEW Name: "); scanf(" %[^\n]",d.name);
            printf("Enter NEW Speciality: "); scanf(" %[^\n]",d.speciality);
        }
        fprintf(tmp,"%d %s %s\n",d.id,d.name,d.speciality);
    }
    fclose(fp); fclose(tmp);
    remove("doctors.txt"); rename("temp.txt","doctors.txt");
    if(found) printf("Doctor updated successfully!\n"); else printf("Doctor not found!\n");
}

void sortDoctorsAZ() {
    FILE *fp=fopen("doctors.txt","r");
    struct Doctor arr[MAX_DOCTORS],temp;
    int count=0;
    while(fscanf(fp,"%d %s %s",&arr[count].id,arr[count].name,arr[count].speciality)!=EOF) count++;
    fclose(fp);
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(strcmp(arr[i].name,arr[j].name)>0){ temp=arr[i]; arr[i]=arr[j]; arr[j]=temp; }
        }
    }
    printf("\n---- Doctors A-Z ----\n");
    for(int i=0;i<count;i++) printf("ID:%d Name:%s Speciality:%s\n",arr[i].id,arr[i].name,arr[i].speciality);
}

void doctorStats() {
    FILE *fp=fopen("doctors.txt","r");
    struct Doctor d; int count=0;
    while(fscanf(fp,"%d %s %s",&d.id,d.name,d.speciality)!=EOF) count++;
    fclose(fp);
    printf("Total Doctors: %d\n",count);
}

/////////////////////////////////////////////////////////
//                APPOINTMENT FUNCTIONS
/////////////////////////////////////////////////////////
void addAppointment() {
    FILE *fp=fopen("appointments.txt","a");
    struct Appointment a;
    printf("Enter Patient ID: "); scanf("%d",&a.patientId);
    printf("Enter Doctor ID: "); scanf("%d",&a.doctorId);
    printf("Enter Date (DD-MM-YYYY): "); scanf("%s",a.date);
    fprintf(fp,"%d %d %s\n",a.patientId,a.doctorId,a.date);
    fclose(fp);
    printf("Appointment created!\n");
}

void viewAppointments() {
    FILE *fp=fopen("appointments.txt","r");
    struct Appointment a;
    printf("\n---- Appointment List ----\n");
    while(fscanf(fp,"%d %d %s",&a.patientId,&a.doctorId,a.date)!=EOF){
        printf("Patient ID:%d Doctor ID:%d Date:%s\n",a.patientId,a.doctorId,a.date);
    }
    fclose(fp);
}

void deleteAppointment() {
    FILE *fp=fopen("appointments.txt","r");
    FILE *tmp=fopen("temp.txt","w");
    struct Appointment a; int pId,dId; char date[20];
    printf("Enter Patient ID: "); scanf("%d",&pId);
    printf("Enter Doctor ID: "); scanf("%d",&dId);
    printf("Enter Date: "); scanf("%s",date);
    while(fscanf(fp,"%d %d %s",&a.patientId,&a.doctorId,a.date)!=EOF){
        if(!(a.patientId==pId && a.doctorId==dId && strcmp(a.date,date)==0))
            fprintf(tmp,"%d %d %s\n",a.patientId,a.doctorId,a.date);
    }
    fclose(fp); fclose(tmp);
    remove("appointments.txt"); rename("temp.txt","appointments.txt");
    printf("Appointment deleted!\n");
}

/////////////////////////////////////////////////////////
//                   AMBULANCE FUNCTIONS
/////////////////////////////////////////////////////////
void addAmbulance() {
    FILE *fp=fopen("ambulance.txt","a");
    struct Ambulance amb;
    printf("Enter Ambulance ID: "); scanf("%d",&amb.id);
    printf("Enter Driver Name: "); scanf(" %[^\n]", amb.driverName);
    printf("Enter Phone: "); scanf(" %[^\n]", amb.phone);
    fprintf(fp,"%d %s %s\n",amb.id,amb.driverName,amb.phone);
    fclose(fp);
    printf("Ambulance added!\n");
}

void viewAmbulance() {
    FILE *fp=fopen("ambulance.txt","r");
    struct Ambulance amb;
    printf("\n---- Ambulance List ----\n");
    while(fscanf(fp,"%d %s %s",&amb.id,amb.driverName,amb.phone)!=EOF)
        printf("ID:%d Driver:%s Phone:%s\n",amb.id,amb.driverName,amb.phone);
    fclose(fp);
}

/////////////////////////////////////////////////////////
//                   BILLING FUNCTIONS
/////////////////////////////////////////////////////////
void generateBill() {
    int pid;
    float consultationFee, medicineFee, labFee, total;
    printf("Enter Patient ID for billing: "); scanf("%d",&pid);
    printf("Enter Consultation Fee: "); scanf("%f",&consultationFee);
    printf("Enter Medicine Fee: "); scanf("%f",&medicineFee);
    printf("Enter Lab Fee: "); scanf("%f",&labFee);
    total = consultationFee + medicineFee + labFee;
    printf("\n----- BILL -----\nPatient ID: %d\nConsultation: %.2f\nMedicine: %.2f\nLab: %.2f\nTOTAL: %.2f\n",pid,consultationFee,medicineFee,labFee,total);
}
