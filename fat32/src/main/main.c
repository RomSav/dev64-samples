#include <stdio.h>
#include <stdlib.h>
#include <hdd/api.h>
#include <fat32/api.h>
#include <test/api.h>


int main(int argc, char *argv[])
{
  HDD_CB_T hdd_cb;
  FAT32_CB_T cb;
  FAT32_DIR_ENTRY_T entry;
  UINT32 cluster;

  bool result = hdd_open_device(&hdd_cb, 1);
  printf( result ?
    "active partition start sector %x\n" : "false" , hdd_cb.lbaStart );

  result = result && fat32_open_device(&cb, &hdd_cb);
  if (result) {
    fat32_print_control_block(&cb);

    memset(&entry, 0, sizeof(entry));
    memcpy(entry.DIR_Name, "KERNEL     ", sizeof(entry.DIR_Name));
    result = fat32_search_root_dir(&cb, &entry);
    printf(result ? "search success\n" : "search failure\n");

    if (result) {
      cluster = (entry.DIR_FstClusHI << 16) | entry.DIR_FstClusLO;
      result = fat32_print_cluster_chain(&cb, 3);
      printf(result ? "success\n" : "failure\n");
    }
  }
  return 0;
}

