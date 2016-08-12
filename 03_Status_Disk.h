char Status_Disk(char *Disk, long *Total, long *Used){
//*************************************************************************************************************************
// Disk
    struct statfs Disk_Information;
    statfs(Disk, &Disk_Information);
    long Block_Size = Disk_Information.f_bsize;
    *Total  = Block_Size * Disk_Information.f_blocks;
    *Used   = (*Total) - (Disk_Information.f_bfree * Block_Size);
    return 'V';
}
