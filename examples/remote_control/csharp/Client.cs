using System;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    class Client
    {
        static void Main(string[] args)
        {

            // open named pipe on client site
            var client = new NamedPipeClientStream("CanppServerPipe");
            client.Connect();
            StreamReader reader = new StreamReader(client);
            StreamWriter writer = new StreamWriter(client);
            
            // write start command to CAN++
            writer.Write("START\n");
            writer.Flush();

            // write special command to CAN++
            System.Threading.Thread.Sleep(2000);
            writer.Write("COMMAND:TEST1\n");
            writer.Flush();

            // write stop command to CAN++
            System.Threading.Thread.Sleep(5000);
            writer.Write("STOP\n");
            writer.Flush();


        }


    }
}
