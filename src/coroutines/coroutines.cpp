#include "common/table.hpp"
#include "net_coroutines.hpp"

using namespace net_coroutines;

int main()
{
    const auto t = table();
    auto sock = bind_local("socket");
    sock.listen();

    spawn([&t, sock = std::move(sock)](auto& yield) mutable {
        for (;;) {
            auto conn = sock.accept(yield);

            spawn([&t, conn = std::move(conn)](auto& yield) mutable {
                while (auto req = conn.recv(yield)) {
                    auto result = t.lookup(*req);
                    conn.send(result);
                }
            });
        }
    });

    loop();
}
