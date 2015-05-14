import java.awt.Graphics;

class HelloWorldApplet extends java.applet.Applet{

	public void paint(Graphics g){
		g.drawstring("Hello, world!",5,25);
	}
}