/************************************************
 * Coded by Bann
 * Project: The Forgotten Darkness
 * Function: Login GUI
 * Jan 1st, 2011
************************************************/



using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Data;
using System.Net;
using System.Net.Sockets;


public class Login : Form
{
    private Button exit, connect;
    private TextBox username, password;
    private PictureBox logo;
    private Label nLabel, pwLabel, sLabel, tLabel;
    private ListBox serverBox;
    //private ClientTest() clt = new ClientTest();

    [DllImport("Gdi32.dll", EntryPoint = "CreateRoundRectRgn")]
    private static extern IntPtr CreateRoundRectRgn
    (
        int nLeftRect,
        int nTopRect,
        int nRightRect,
        int nBottomRect,
        int nWidthEllipse,
        int nHeightEllipse
    );

    public Login()
        : base()
    {
        this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
        this.ClientSize = new System.Drawing.Size(500, 400);
        this.MaximumSize = new Size(500, 400);
        this.MinimumSize = new Size(500, 400);
        this.Text = "Forgotten Darkness";
        this.BackColor = Color.BlanchedAlmond;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.FormBorderStyle = FormBorderStyle.None;
        this.Cursor = Cursors.Arrow;

        Region = System.Drawing.Region.FromHrgn(CreateRoundRectRgn(0, 0, Width, Height, 450, 39));

        SetBackground();
        Username();
        Password();
        ExitButton();
        ConnectButton();
        AccountLabel();
        PasswordLabel();
        TitleLabel();
    }

    private void SetBackground()
    {
        Bitmap myBg = new Bitmap("theBack.bmp");
        //this.BackgroundImage = RoundCorners(myBg, 20, Color.White);
        this.BackgroundImage = myBg;
    }

    private void Username()
    {
        username = new TextBox();
        username.Location = new Point(200, 80);
        username.Name = "UName";
        username.TabIndex = 1;
        username.Text = "Username";
        username.MaxLength = 12;
        username.Click += new EventHandler(OnMouseClickName);
        //username.KeyDown += new KeyEventHandler(KeyEnter);

        Controls.Add(username);
    }

    private void AccountLabel()
    {
        nLabel = new Label();
        nLabel.Name = "Nlbl";
        nLabel.Text = "Account";
        nLabel.Location = new Point(220, 60);
        nLabel.Size = new Size(100, 15);
        nLabel.BackColor = Color.Transparent;
        nLabel.ForeColor = Color.Goldenrod;
        nLabel.Font = new Font("Arial", 10, FontStyle.Bold);
        Controls.Add(nLabel);
    }

    
    private void Password()
    {
        password = new TextBox();
        password.Location = new Point(200, 130);
        password.Name = "Pwrd";
        password.TabIndex = 2;
        password.Text = "Password";
        password.MaxLength = 12;
        password.Click += new EventHandler(OnMouseClickPassword);

        Controls.Add(password);
    }

    private void PasswordLabel()
    {
        pwLabel = new Label();
        pwLabel.Name = "Plbl";
        pwLabel.Text = "Password";
        pwLabel.Location = new Point(215, 110);
        pwLabel.Size = new Size(100, 15);
        pwLabel.BackColor = Color.Transparent;
        pwLabel.ForeColor = Color.Goldenrod;
        pwLabel.Font = new Font("Arial", 10, FontStyle.Bold);
        Controls.Add(pwLabel);
    }


    private void ExitButton()
    {
        exit = new Button();
        exit.Text = "Close";
        exit.Location = new Point(194, 380);
        exit.TabIndex = 3;
        exit.Size = new System.Drawing.Size(110, 20);
        exit.Font = new Font("Lucida Sans", 8, FontStyle.Bold);
        exit.ForeColor = Color.Gold;
        exit.BackColor = Color.Black;
        exit.Cursor = Cursors.Hand;
        exit.Click += new EventHandler(Close);

        Controls.Add(exit);
    }

    private void ConnectButton()
    {
        connect = new Button();
        connect.Text = "Connect";
        connect.Location = new Point(172, 175);
        connect.TabIndex = 4;
        connect.Size = new System.Drawing.Size(160, 30);
        connect.Font = new Font("Lucida Sans", 12, FontStyle.Bold);
        connect.ForeColor = Color.Black;
        connect.BackColor = Color.Gold;
        connect.Cursor = Cursors.Hand;

        Controls.Add(connect);
    }

    private void TitleLabel()
    {
        tLabel = new Label();
        tLabel.Text = "The Forgotten Darkness";
        tLabel.Name = "TLbl";
        tLabel.Size = new Size(450, 50);
        tLabel.Location = new Point(50, 320);
        tLabel.BackColor = Color.Transparent;
        tLabel.ForeColor = Color.Crimson;
        tLabel.Font = new Font("Arial", 27, FontStyle.Italic);
        Controls.Add(tLabel);
    }

    private void OnMouseClickName(object sender, EventArgs args)
    {
        if (username.Text == "Username")
        {
            username.Clear();
        }
    }

    private void OnMouseClickPassword(object sender, EventArgs args)
    {
        if (password.Text == "Password")
        {
            password.Clear();
        }
    }

    private void Close(Object sender, EventArgs args)
    {
        Application.Exit();
    }

    public Image RoundCorners(Image StartImage, int CornerRadius, Color BackgroundColor)
    {
        CornerRadius *= 2;
        Bitmap RoundedImage = new Bitmap(StartImage.Width, StartImage.Height);

        Graphics g = Graphics.FromImage(RoundedImage);
        g.Clear(BackgroundColor);
        g.SmoothingMode = SmoothingMode.AntiAlias;

        Brush brush = new TextureBrush(StartImage);

        GraphicsPath gp = new GraphicsPath();
        gp.AddArc(0, 0, CornerRadius, CornerRadius, 180, 90);
        gp.AddArc(RoundedImage.Width - CornerRadius, 0, CornerRadius, CornerRadius, 270, 90);
        gp.AddArc(RoundedImage.Width - CornerRadius, RoundedImage.Height - CornerRadius, CornerRadius,
            CornerRadius, 0, 90);
        gp.AddArc(0, RoundedImage.Width - CornerRadius, CornerRadius, CornerRadius, 90, 90);

        g.FillPath(brush, gp);
        return RoundedImage;
    }


    public static void Main()
    {
        Application.Run(new Login());
    }
}

