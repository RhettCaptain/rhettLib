using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Threading;

using System.Windows.Forms;


namespace SrvRob
{
    class SocketServer
    {
        private IPEndPoint ipEndPoint;
        private Socket sockServer;
        private ArrayList sockClients;
        private Thread acceptThread;
        private const byte EOF = 255; 
       
        public SocketServer(string ip, int port, int count = 10)
        {
            sockClients = new ArrayList();
            ipEndPoint = new IPEndPoint(IPAddress.Parse(ip), port);
            sockServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            sockServer.Bind(ipEndPoint);
            sockServer.Listen(count);
            acceptThread = new Thread(new ThreadStart(keepAccept));
            acceptThread.IsBackground = true;
            acceptThread.Start();
        }

        public void send(int idx, string str)
        {
            if (idx < 0 || idx > sockClients.Count || sockClients[idx] == null)
            {
                MessageBox.Show("err client idx");
            }
            else
            {
                ((Socket)sockClients[idx]).Send(Encoding.ASCII.GetBytes(str));
            }
        }

        public void sendFile(int idx,string path)
        {
            if (idx < 0 || idx > sockClients.Count || sockClients[idx] == null)
            {
                MessageBox.Show("err client idx");
            }
            else
            {
                ((Socket)sockClients[idx]).SendFile(path);
                byte[] tail = new byte[1];
                tail[0] = EOF;
                ((Socket)sockClients[idx]).Send(tail);
            }
        }
        public string recieve(int idx)
        {

            if (idx < 0 || idx > sockClients.Count || sockClients[idx] == null)
            {
                MessageBox.Show("err client idx");
                return "";
            }
            else
            {
                byte[] buffer = new byte[1000];
                ((Socket)sockClients[idx]).Receive(buffer);
                string content = System.Text.Encoding.Default.GetString(buffer);
                return content;
            }
        }

        public string readline(int idx,char eol='\n')
        {
            if (idx < 0 || idx > sockClients.Count || sockClients[idx] == null)
            {
                MessageBox.Show("err client idx");
                return "";
            }
            else
            {
                byte[] buffer = new byte[1000];
                byte[] ch = new byte[1];
                ch[0] = (byte)' ';
                int bit = 0;
                while (bit < 1000)
                {
                    if (((Socket)sockClients[idx]).Receive(ch) > 0)
                    {
                        if (ch[0] == eol)
                        {
                            break;
                        }
                        buffer[bit] = ch[0];
                        bit++;
                    }
                }
                buffer[bit] = 0;
                string content = System.Text.Encoding.Default.GetString(buffer);
                return content;
            }
        }

        public string recieveFile(int idx,string path)
        {
            if (idx < 0 || idx > sockClients.Count || sockClients[idx] == null)
            {
                MessageBox.Show("err client idx");
                return "";
            }
            else
            {
                byte[] buffer = new byte[1];
                ArrayList content = new ArrayList();
                do
                {
                    ((Socket)sockClients[idx]).Receive(buffer);
                    content.Add(buffer[0]);
                } while (buffer[0] != EOF);
                content.RemoveAt(content.Count - 1);      
                return content.ToString();
            }
        }

        public int getClientCount()
        {
            return sockClients.Count;
        }

        private void keepAccept()
        {
            while (true)
            {
                Socket sockClient = sockServer.Accept();
                sockClients.Clear();        //for only one client situation
                sockClients.Add(sockClient);
            }
            
        }
    }

    class SocketClient
    {
        private IPEndPoint ipEndPoint;
        private Socket sockClient;
        private const byte EOF = 255;
        public SocketClient(string ip, int port)
        {
            ipEndPoint = new IPEndPoint(IPAddress.Parse(ip), port);
            sockClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            sockClient.Connect(ipEndPoint);
        }

        public void send(string str)
        {
            sockClient.Send(Encoding.ASCII.GetBytes(str));
        }

        public void sendFile(string path)
        {
            sockClient.SendFile(path);
            byte[] tail = new byte[1];
            tail[0] = EOF;
            sockClient.Send(tail);
        }

        public string recieve()
        {
            byte[] buffer = new byte[1000];
            sockClient.Receive(buffer);
            string content = System.Text.Encoding.Default.GetString(buffer);
            return content;
        }

        public string recieveFile(string path)
        {
            byte[] buffer = new byte[1];
            ArrayList content = new ArrayList();
            do
            {
                sockClient.Receive(buffer);
                content.Add(buffer[0]);
            } while (buffer[0] != EOF);
            content.RemoveAt(content.Count - 1);
            string res = System.Text.Encoding.Default.GetString(buffer);
            return res;
        }
    }
}
