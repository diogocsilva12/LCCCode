-module(sum_server).
-export([start/0, server/0, stats_service/2, handle_client/1]).

start() -> 
    StatsService = spawn(fun() -> stats_service(0, 0) end),
    register(stats, StatsService),
    spawn(fun() -> server() end).

% Stats service to maintain global sum and count
stats_service(GlobalSum, GlobalCount) ->
    receive
        {add_number, Number} ->
            stats_service(GlobalSum + Number, GlobalCount + 1);
        {get_average, Pid} ->
            case GlobalCount of
                0 -> 
                    Pid ! {average, undefined},
                    stats_service(GlobalSum, GlobalCount);
                _ -> 
                    Pid ! {average, GlobalSum / GlobalCount},
                    stats_service(GlobalSum, GlobalCount)
            end
    end.

server() ->
    {ok, ListenSocket} = gen_tcp:listen(8000, [{packet, line}, {reuseaddr, true}]),
    io:format("Server started on port 8000~n"),
    accept_connections(ListenSocket).

accept_connections(ListenSocket) ->
    {ok, Socket} = gen_tcp:accept(ListenSocket),
    io:format("New client connected~n"),
    spawn(fun() -> handle_client(Socket) end),
    accept_connections(ListenSocket).

handle_client(Socket) ->
    handle_numbers(Socket, 0, 0).

handle_numbers(Socket, Sum, Count) ->
    case gen_tcp:recv(Socket, 0) of
        {ok, Data} ->
            try
                Number = list_to_integer(string:trim(binary_to_list(Data))),
                
                % Update client's local sum
                NewSum = Sum + Number,
                gen_tcp:send(Socket, list_to_binary(integer_to_list(NewSum) ++ "\n")),
                
                % Update global stats
                stats ! {add_number, Number},
                
                handle_numbers(Socket, NewSum, Count + 1)
            catch
                _:_ ->
                    gen_tcp:send(Socket, list_to_binary("Error: Invalid number\n")),
                    handle_numbers(Socket, Sum, Count)
            end;
        {error, closed} ->
            % Send client's average
            if 
                Count > 0 -> 
                    ClientAvg = Sum / Count,
                    gen_tcp:send(Socket, list_to_binary(io_lib:format("Your average: ~.2f\n", [ClientAvg])));
                true -> 
                    gen_tcp:send(Socket, list_to_binary("You didn't send any numbers\n"))
            end,
            
            % Send global average
            stats ! {get_average, self()},
            receive
                {average, undefined} ->
                    gen_tcp:send(Socket, list_to_binary("No global average available\n"));
                {average, GlobalAvg} ->
                    gen_tcp:send(Socket, list_to_binary(io_lib:format("Global average: ~.2f\n", [GlobalAvg])))
            end,
            
            io:format("Client disconnected~n"),
            gen_tcp:close(Socket);
        {error, Reason} ->
            io:format("Socket error: ~p~n", [Reason]),
            gen_tcp:close(Socket)
    end.