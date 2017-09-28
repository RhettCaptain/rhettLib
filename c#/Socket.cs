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
                return buffer.ToString();
            }
        }

        public int getClientCount()
        {
            return sockClients.Count;
        }

        private void keepAccept()
        {
            Socket sockClient = sockServer.Accept();
            sockClients.Add(sockClient);
        }
    }

    class SocketClient
    {
        private IPEndPoint ipEndPoint;
        private Socket sockClient;
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

        public string recieve()
        {
            byte[] buffer = new byte[1000];
            sockClient.Receive(buffer);
            return buffer.ToString();
        }
    }
}
