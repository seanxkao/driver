#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define DEV_NAME "mydriver"

//member
dev_t dev;
struct cdev char_dev;

//method

MODULE_LICENSE("GPL");


loff_t scull_llseek(struct file*, loff_t, int);
ssize_t scull_read(struct file*, char __user*, size_t, loff_t*);
ssize_t scull_write(struct file*, const char __user*, size_t, loff_t*);
int scull_ioctl(struct inode*, struct file*, unsigned int, unsigned long);
int scull_open(struct inode*, struct file*);
int scull_release(struct inode*, struct file*);

struct file_operations scull_fops = {
	.owner	 = THIS_MODULE,
//	.llseek  = scull_llseek,
	.read 	 = scull_read,
	.write	 = scull_write,
//	.unlocked_ioctl	 = scull_ioctl,
	.open	 = scull_open,
	.release = scull_release,
};


int init_module(){
	int err; 
	alloc_chrdev_region(&dev, 0, 8, DEV_NAME);
	printk(KERN_INFO "Register char dev %d.%d\n", MAJOR(dev), MINOR(dev));
	cdev_init(&char_dev, &scull_fops);
	char_dev.owner = THIS_MODULE;
	char_dev.ops = &scull_fops;
	err = cdev_add(&char_dev, dev, 1);
	if(err)printk(KERN_NOTICE "error");
	return 0;
}

void cleanup_module(){
	printk(KERN_INFO "Unregister char dev %d.%d\n", MAJOR(dev), MINOR(dev));
	cdev_del(&char_dev);
	unregister_chrdev_region(dev, 8);
}



int scull_open(struct inode *inode, struct file *filp){
	printk(KERN_INFO "mydriver: open\n");
	return 0;
}
int scull_release(struct inode *inode, struct file *filp){
	printk(KERN_INFO "mydriver: release\n");
	return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t size, loff_t *fpos){
	printk(KERN_INFO "mydriver: read \n");
	return 0;
}
ssize_t scull_write(struct file *filp, const char __user *buf, size_t size, loff_t *fpos){
	printk(KERN_INFO "mydriver: write \n");
	return size;
}
