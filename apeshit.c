#define pr_fmt(fmt) "[" KBUILD_MODNAME "]: " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>

/**
*
* Have an ascii Gorilla - http://www.chris.com/ascii/index.php?art=animals/gorillas
*
*                 _
*             ,.-" "-.,
*            /   ===   \
*           /  =======  \
*        __|  (o)   (0)  |__      
*       / _|    .---.    |_ \         
*      | /.----/ O O \----.\ |       
*       \/     |     |     \/        
*       |                   |            
*       |                   |           
*       |                   |          
*       _\   -.,_____,.-   /_         
*   ,.-"  "-.,_________,.-"  "-.,
*  /          |       |          \  
* |           l.     .l           | 
* |            |     |            |
* l.           |     |           .l             
*  |           l.   .l           | \,     
*  l.           |   |           .l   \,    
*   |           |   |           |      \,  
*   l.          |   |          .l        |
*    |          |   |          |         |
*    |          |---|          |         |
*    |          |   |          |         |
*    /"-.,__,.-"\   /"-.,__,.-"\"-.,_,.-"\
*   |            \ /            |         |
*   |             |             |         |
*    \__|__|__|__/ \__|__|__|__/ \_|__|__/ Sandra
*
*/

#include <trk1.h>

#define DEVICE_NAME "apeshit"	/* Dev name as it appears in /proc/devices   */

struct apeshit {
	char	*msg;
	bool	first_time;
	int	current_track;
};

static char *tracks[] = {apeshit_cpi_trk1};

static char *tracknames[] = {"Shaved Ape Drape"};

static unsigned long tracklens[] = {APESHIT_CPI_TRK1_LEN};

static int device_open(struct inode *inode, struct file *file)
{
	struct apeshit *apeshit;

	apeshit = kzalloc(sizeof(*apeshit), GFP_KERNEL);
	if (!apeshit)
		return -ENOMEM;

	apeshit->first_time = true;
	apeshit->msg = tracks[0];	/* track 1 */
	file->private_data = apeshit;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	struct apeshit *apeshit = file->private_data;

	kfree(apeshit);
	return 0;
}

static ssize_t device_read(struct file *file,
			   char *buffer,
			   size_t length,
			   loff_t *offset)
{
	struct apeshit *apeshit = file->private_data;
	int current_track = apeshit->current_track;

	int bytes_read = 0;

	if (apeshit->first_time == true) {
		pr_info("Now playing track %d - %s\n",
			current_track + 1, tracknames[current_track]);
		apeshit->first_time = false;
	}

	if (apeshit->msg - tracks[current_track] >= tracklens[current_track]) {
		/* End of Track.  Skip to next track, or finish if it's track 6 */
		current_track++;
		if (current_track >= 6)
			current_track = 0;
		pr_info("Now playing track %d - %s\n",
			current_track + 1, tracknames[current_track]);
		apeshit->msg = tracks[current_track];
		apeshit->current_track = current_track;
	}

	while (length &&
		(apeshit->msg - tracks[current_track]) <
		 tracklens[current_track]) {
		put_user(*(apeshit->msg++), buffer++);

		length--;
		bytes_read++;
	}

	return bytes_read;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	pr_err("Writing to apeshit - Shaved Ape Drape isn't supported.\n");
	return -EINVAL;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static struct miscdevice apeshit_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &fops,
	.mode = S_IRUGO,
};

static int apeshit_init(void)
{
	int ret;

	ret = misc_register(&apeshit_dev);
	if (ret) {
		pr_err("misc device register failed\n");
		return ret;
	}
	pr_info("Apeshit Simians- Shaved Ape Drape - Kernel Module Edition - 2014\n");
	pr_info("Apeshit Simians are Boutros Boutros Gorilla, Surnom de Gorille, Gorilla Monpoo\n");
	pr_info("On the web at http://soundcloud.com/apeshit-simians\n");
	pr_info("'ogg123 - < /dev/apeshit' to play.\n");

	return 0;
}

static void apeshit_exit(void)
{
	misc_deregister(&apeshit_dev);
}

module_init(apeshit_init);
module_exit(apeshit_exit);
