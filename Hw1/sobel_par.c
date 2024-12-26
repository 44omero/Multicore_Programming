/* Example sobel code*/
/* By Vince Weaver <vincent.weaver@maine.edu> */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>

#include <jpeglib.h>


/* Filters */
static int sobel_x_filter[3][3]={{-1,0,+1},{-2,0,+2},{-1,0,+1}};
static int sobel_y_filter[3][3]={{-1,-2,-1},{0,0,0},{1,2,+1}};

/* Structure describing the image */
struct image_t {
	int x;
	int y;
	int depth;	/* bytes */
	unsigned char *pixels;
};
//we can divide the image by row row then do both sobelx and y on this
struct convolve_data_t {
	struct image_t *old;
	struct image_t *new;
	int (*filter)[3][3];
	int start_row;
	int end_row;
};


/* convolve code */
static void *generic_convolve(void *argument) {

	int x,y,k,l,d;
	uint32_t color;
	int sum,depth,width;

	struct image_t *old;
	struct image_t *new;
	int (*filter)[3][3];
	struct convolve_data_t *data;

	/* Convert from void pointer to the actual data type */
	data=(struct convolve_data_t *)argument;
	old=data->old;
	new=data->new;
	filter=data->filter;

	depth=old->depth;
	width=old->x*old->depth;


	for(d=0;d<depth;d++) {
		for(x=1;x<old->x-1;x++){
			for(y=data->start_row;y<data->end_row;y++){
				
				sum=0;
				for(k=-1;k<2;k++) {
					for(l=-1;l<2;l++) {
						int index = ((y+l)*width) + ((x+k)*depth+d); //i calculate this first (did this while debugging code)
            			color = old->pixels[index];
            			sum += color * (*filter)[k+1][l+1];
		   			}
				}

			if (sum<0) sum=0;
			if (sum>255) sum=255;

			new->pixels[(y*width)+x*depth+d]=sum;
				}
			}
	}

	return NULL;
}

static int load_jpeg(char *filename, struct image_t *image) {

	FILE *fff;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW output_data;
	unsigned int scanline_len;
	int scanline_count=0;

	fff=fopen(filename,"rb");
	if (fff==NULL) {
		fprintf(stderr, "Could not load %s: %s\n",
			filename, strerror(errno));
		return -1;
	}

	/* set up jpeg error routines */
	cinfo.err = jpeg_std_error(&jerr);

	/* Initialize cinfo */
	jpeg_create_decompress(&cinfo);

	/* Set input file */
	jpeg_stdio_src(&cinfo, fff);

	/* read header */
	jpeg_read_header(&cinfo, TRUE);

	/* Start decompressor */
	jpeg_start_decompress(&cinfo);

	printf("output_width=%d, output_height=%d, output_components=%d\n",
		cinfo.output_width,
		cinfo.output_height,
		cinfo.output_components);

	image->x=cinfo.output_width;
	image->y=cinfo.output_height;
	image->depth=cinfo.output_components;

	scanline_len = cinfo.output_width * cinfo.output_components;
	image->pixels=malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components);

	while (scanline_count < cinfo.output_height) {
		output_data = (image->pixels + (scanline_count * scanline_len));
		jpeg_read_scanlines(&cinfo, &output_data, 1);
		scanline_count++;
	}

	/* Finish decompressing */
	jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(fff);

	return 0;
}

static int store_jpeg(char *filename, struct image_t *image) {

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	int quality=90; /* % */
	int i;

	FILE *fff;

	JSAMPROW row_pointer[1];
	int row_stride;

	/* setup error handler */
	cinfo.err = jpeg_std_error(&jerr);

	/* initialize jpeg compression object */
	jpeg_create_compress(&cinfo);

	/* Open file */
	fff = fopen(filename, "wb");
	if (fff==NULL) {
		fprintf(stderr, "can't open %s: %s\n",
			filename,strerror(errno));
		return -1;
	}

	jpeg_stdio_dest(&cinfo, fff);

	/* Set compression parameters */
	cinfo.image_width = image->x;
	cinfo.image_height = image->y;
	cinfo.input_components = image->depth;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);

	/* start compressing */
	jpeg_start_compress(&cinfo, TRUE);

	row_stride=image->x*image->depth;

	for(i=0;i<image->y;i++) {
		row_pointer[0] = & image->pixels[i * row_stride];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	/* finish compressing */
	jpeg_finish_compress(&cinfo);

	/* close file */
	fclose(fff);

	/* clean up */
	jpeg_destroy_compress(&cinfo);

	return 0;
}

static int combine(struct image_t *s_x, struct image_t *s_y,struct image_t *new) {
	int i;
	int out;

	for(i=0;i<( s_x->depth * s_x->x * s_x->y );i++) {

		out=sqrt(
			(s_x->pixels[i]*s_x->pixels[i])+
			(s_y->pixels[i]*s_y->pixels[i])
			);
		if (out>255) out=255;
		if (out<0) out=0;
		new->pixels[i]=out;
	}

	return 0;
}

int main(int argc, char **argv) {

	/* Check command line usage */ //changed for thread count
	if (argc<3) {
		fprintf(stderr,"Usage: %s image_file thread_count\n",argv[0]);
		return -1;
	}
	//get thread count
	int thread_count = atoi(argv[2]);
	//at least 1 thread needed
	if(thread_count<1) {
		printf("Use proper thread count");
		return 1;
		}
	
	pthread_t *threads;
	struct convolve_data_t *thread_data_x, *thread_data_y;
	struct image_t image, new_image, sobel_x, sobel_y;



	/* Load an image */ //control if it fails
	if (load_jpeg(argv[1], &image) != 0) {
        fprintf(stderr, "Failed to load image\n");
        return -1;
    }

	/* Allocate space for output image */
	new_image.x=image.x;
	new_image.y=image.y;
	new_image.depth=image.depth;
	new_image.pixels=malloc(image.x*image.y*image.depth*sizeof(char));

	/* Allocate space for output image */
	sobel_x.x=image.x;
	sobel_x.y=image.y;
	sobel_x.depth=image.depth;
	sobel_x.pixels=malloc(image.x*image.y*image.depth*sizeof(char));

	sobel_y.x=image.x;
	sobel_y.y=image.y;
	sobel_y.depth=image.depth;
	sobel_y.pixels=malloc(image.x*image.y*image.depth*sizeof(char));


	//checked allocation
	if (!new_image.pixels || !sobel_x.pixels || !sobel_y.pixels) {
        fprintf(stderr, "Failed to allocate memory for output images\n");
        // Free any successfully allocated memory
        free(new_image.pixels);
        free(sobel_x.pixels);
        free(sobel_y.pixels);
        free(image.pixels);
        return -1;
    }
	//allocate for thread 
	threads = malloc(thread_count * sizeof(pthread_t));
    thread_data_x = malloc(thread_count * sizeof(struct convolve_data_t));
    thread_data_y = malloc(thread_count * sizeof(struct convolve_data_t));
	//parallelize

	//calculate row per thread
	//for sobelx
	int rows_per_thread = image.y / thread_count;
	int remaining_rows = image.y % thread_count;
	for (int i = 0; i < thread_count; i++) {
		thread_data_x[i].old = &image;
		thread_data_x[i].new = &sobel_x;
		thread_data_x[i].filter = &sobel_x_filter;
		thread_data_x[i].start_row = i * rows_per_thread;
		thread_data_x[i].end_row = (i + 1) * rows_per_thread;
		if (i == thread_count - 1) {
			thread_data_x[i].end_row += remaining_rows;
		}

		if (pthread_create(&threads[i], NULL, generic_convolve, (void *)&thread_data_x[i]) != 0) {
    		fprintf(stderr, "Error creating thread %d\n", i);
    		return -1;
		}
	}

	//join the threads
	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i], NULL);
	}

	//for sobely
	for (int i = 0; i < thread_count; i++) {
		thread_data_y[i].old = &image;
		thread_data_y[i].new = &sobel_y;
		thread_data_y[i].filter = &sobel_y_filter;
		thread_data_y[i].start_row = i * rows_per_thread;
		thread_data_y[i].end_row = (i + 1) * rows_per_thread;
		if (i == thread_count - 1) {
			thread_data_y[i].end_row += remaining_rows;
		}

		pthread_create(&threads[i], NULL, generic_convolve, (void *)&thread_data_y[i]);
	}

	//join the threads
	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i], NULL);
	}

	/* Combine to form output */
	combine(&sobel_x,&sobel_y,&new_image);

	/* Write data back out to disk */
	store_jpeg("out.jpg",&sobel_x);
	//free some allocations
	free(threads);
	free(thread_data_y);
	free(thread_data_x);

	free(image.pixels);
	free(new_image.pixels);
	free(sobel_x.pixels);
	free(sobel_y.pixels);
	return 0;
}
