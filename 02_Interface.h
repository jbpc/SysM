char Interface(void){
//*************************************************************************************************************************
// Time
    time_t TIME;
    time(&TIME);
// Disk
    char    *Disk_Main              = "/";
    long    Disk_Total              = 0;
    long    Disk_Used               = 0;
    Status_Disk(Disk_Main, &Disk_Total, &Disk_Used);
    double  Disk_Percentage         = 100 * ((double)Disk_Used / (double)Disk_Total);

    char    *Disk_Home              = "/home";
    long    Disk_home_Total         = 0;
    long    Disk_home_Used          = 0;
    Status_Disk(Disk_Home, &Disk_home_Total, &Disk_home_Used);
    double  Disk_home_Percentage    = 100 * ((double)Disk_home_Used / (double)Disk_home_Total);
// Memory
    long    Memory_Total            = 0;
    long    Memory_Used             = 0;
    Status_Memory(&Memory_Total, &Memory_Used);
    double  Memory_Percentage       = 100 * ((double)(Memory_Used) / (double)(Memory_Total));
// CPU
    double  CPU_Percentage          = Status_Cpu();
// Network
    double  Network_Sent_Rate       = 0;
    double  Network_Received_Rate   = 0;
    Status_Network(&Network_Sent_Rate, &Network_Received_Rate);
//*************************************************************************************************************************
// Interface
    printf("\n\n\n\n\n");
    printf("Current time            %s",        ctime(&TIME));
    printf("File open limit         %ld\n",     sysconf(_SC_OPEN_MAX));
    printf("------------------------------------------------------------\n");
    printf("Disk Total              %ld\n",     Disk_Total);
    printf("Disk Used               %ld\n",     Disk_Used);
    printf("Disk Percentage         %lf%%\n",   Disk_Percentage);
    printf("\n");
    printf("Disk /home Total        %ld\n",     Disk_home_Total);
    printf("Disk /home Used         %ld\n",     Disk_home_Used);
    printf("Disk /home Percentage   %lf%%\n",   Disk_home_Percentage);
    printf("------------------------------------------------------------\n");
    printf("Memory Total            %ld\n",     Memory_Total);
    printf("Memory Used             %ld\n",     Memory_Used);
    printf("Memory Percentage       %lf%%\n",   Memory_Percentage);
    printf("------------------------------------------------------------\n");
    printf("CPU Cores               %ld\n",     sysconf(_SC_NPROCESSORS_CONF));
    printf("CPU Percentage          %lf%%\n",   CPU_Percentage);
    printf("------------------------------------------------------------\n");
    printf("Network Sent rate       %lf\n",     Network_Sent_Rate);
    printf("Network Received rate   %lf\n",     Network_Received_Rate);
    return 'V';
}
