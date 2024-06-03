#ifndef MLXBASE_HPP
#define MLXBASE_HPP

#define WIDTH 480
#define HEIGHT 360

class Mlx
{
	private:
		void	*mlx;
		void	*win;
		void	*img;
		char	*addr;
		int		bits_per_pixel;
		int		line_length;
		int		endian;
	public:
		Mlx();
		~Mlx();
		void	mmlx_init();
		void	*get_mlx();
		void	*get_win();
		void	*get_img();
		char	*get_addr();
		int		get_bits_per_pixel();
		int		get_line_length();
		int		get_endian();
	public:
		void	locate_pixel(int x, int y, int color);
		void	put_image_to_window();
		void	loop_window();
};

#endif