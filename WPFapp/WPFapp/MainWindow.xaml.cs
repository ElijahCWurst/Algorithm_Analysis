using System.DirectoryServices;
using System.Windows;

namespace WPFapp
{
	public partial class MainWindow : Window
	{
		bool running = true;
		public MainWindow()
		{
			InitializeComponent();

			
		}

		private void btnRun_Click(object sender, RoutedEventArgs e)
		{
			if(running)
			{
				tbHello.Text = "Hello, World!";
				btnRun.Content = "End";
			}
			else
			{
				tbHello.Text = "Goodbye, World!";

				tbHello.Text = "";
                btnRun.Content = "Run";
			}
			running = !running;
		}
	}
}