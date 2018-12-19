<<<<<<< HEAD
# SDK for mini2440

#### 项目介绍
1> 支持Nor 启动， tftp烧写
2> 支持Nand启动
3> 支持jffs2文件系统
4> 支持yaffs2文件系统

#### 软件架构
mini2440 从u-boot-> kernel->fs->driver

### 安装教程
u-boot            
	make mini2440_config         
	make all            

kernel              
	make s3c2410_defconfig         
	make menuconfig              
	File system --->        
		Miscellaneous filesystem --->       
		 	<*> YAFFS2 filesystem support    
	make uImage  

#### 使用说明

tftp烧写：
kernel：             
tftp 30000000 uImage   
nand erase 0x00060000 0x200000    
nand write.jffs2 30000000 0x60000 0x200000  

fs：                     
tftp 30000000 fs_mini_mdev.yaffs2      
tftp erase root     
nand write.jffs2 30000000 0x260000 889bc0   

       
nfs :              
bootloader:          
	nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/u-boot.bin     
	nand erase bootloader     
	nand write.jffs2 30000000 bootloader     
   
kernel :    
	nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/uImage    
	nand erase 0x60000 0x200000       
	nand write.jffs2 30000000 0x60000 0x200000      
	 
	// nand erase kernel ; nand write.jffs2 30000000 kernel     
     
fs-yaffs2:        
	nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.yaffs2      
	nand erase root         
	nand write.yaffs 30000000 0x260000 85d640         
        	
  
fs-jffs2           
	nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.jffs2      
	nand erase root                   
	nand write.jffs2 30000000 260000 $filesize           
	set bootargs console=ttySAC0,115200 root=/dev/mtdblock3 rootfstype=jffs2       


nfs-start :   
    // see Documents/nfsroot.txt in linux kernel      
    set bootargs noinitrd root=/dev/nfs nfsroot=192.168.1.133:/home/flinn/mini2440/rootfs/mini_mdev_fs ip=192.168.1.123:192.168.1.133:192.168.1.1:255.255.255.0::eth0:off init=/linuxrc console=ttySAC0        
    save       
   
分区信息 ：              
0x00000000-0x00040000 : "bootloader"    
0x00040000-0x00060000 : "params"   
0x00060000-0x00260000 : "kernel"       
0x00260000-0x10000000 : "root"       

#### 参与贡献

1. Fork 本项目
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request


#### 码云特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. 码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5. 码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6. 码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
=======
# mini2440-SDK
 SDK for mini2440
 
 1> 支持Nor 启动， tftp烧写    
 2> 支持Nand启动         
 3> 支持jffs2文件系统         
 4> 支持yaffs2文件系统      
 
 mini2440 从u-boot-> kernel->fs->driver   
 
u-boot   
  make mini2440_config    
  make all  
  
kernel   
  make s3c2410_defconfig
  make menuconfig    
    File system --->    
      Miscellaneous filesystem --->   
        <*> YAFFS2 filesystem support   
  make uImage   
  
ftp烧写：
kernel：
  tftp 30000000 uImage  
  nand erase 0x00060000 0x200000   
  nand write.jffs2 30000000 0x60000 0x200000  
fs：  
  tftp 30000000 fs_mini_mdev.yaffs2  
  tftp erase root   
  nand write.jffs2 30000000 0x260000 889bc0   
  
nfs :
bootloader:
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/u-boot.bin       
  nand erase bootloader      
  nand write.jffs2 30000000 bootloader         
  
kernel :     
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/uImage    
  nand erase 0x60000 0x200000         
  nand write.jffs2 30000000 0x60000 0x200000      
  // nand erase kernel ; nand write.jffs2 30000000 kernel         


fs-yaffs2:        
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.yaffs2         
  nand erase root           
  nand write.yaffs 30000000 0x260000 85d640         

fs-jffs2     
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.jffs2        
  nand erase root     
  nand write.jffs2 30000000 260000 $filesize        
  set bootargs console=ttySAC0,115200 root=/dev/mtdblock3 rootfstype=jffs2        

nfs-start :
  // see Documents/nfsroot.txt in linux kernel         
  set bootargs noinitrd root=/dev/nfs nfsroot=192.168.1.133:/home/flinn/mini2440/rootfs/mini_mdev_fs   ip=192.168.1.123:192.168.1.133:192.168.1.1:255.255.255.0::eth0:off init=/linuxrc console=ttySAC0      
  save
  
  
分区信息 ：
  0x00000000-0x00040000 : "bootloader"       
  0x00040000-0x00060000 : "params"        
  0x00060000-0x00260000 : "kernel"           
  0x00260000-0x10000000 : "root"        
>>>>>>> 8a45597c758acfcf1dab7d06152acbd00471b19e