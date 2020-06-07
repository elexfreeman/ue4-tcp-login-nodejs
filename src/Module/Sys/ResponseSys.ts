import * as net from "net";


/**
 * Базовый ответ клиенту
 */
export interface BaseResponseI {
    sRoute: string;
    ok: boolean;
    data: any;
    errors: any;
}

/**
 * базовый запрос от клиента
 */
export interface fBaseRequest {
    sClientToken: string;
    sRoute: string;
    data: any;
    ok?: boolean;
    error?: any;
}

/**
 * Функция парсинга запроса от сервера
 * @param data 
 */
export const fRequest = (data: Buffer, sClientToken: string): fBaseRequest => {
    let out: fBaseRequest = {
        sRoute: '',
        data: null,
        ok: true,
        error: null,
        sClientToken: sClientToken,
    }

    try {
        const req: fBaseRequest = JSON.parse(data.toString());

        if (req.sRoute) {
            out.sRoute = req.sRoute;
        }

        if (req.data) {
            out.data = req.data;
        }

        if (req.ok) {
            out.ok = true;
        }

    } catch (e) {
        out.ok = false;
        out.error = e;
    }

    return out;
}

export const fResponse = (socket: net.Socket, response: BaseResponseI) => {
    socket.write(JSON.stringify(response))
}