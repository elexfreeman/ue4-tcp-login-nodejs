/**
 * Модуль для работы с паролем и токеном
 */
const uniqid = require('uniqid');
const crypto = require('crypto');

/**
 * Чек-сумма
 * @param str 
 * @param algorithm 
 * @param encoding 
 */
export function fChecksum(str: string, algorithm?: string, encoding?: string) {
    return crypto
        .createHash(algorithm || 'md5')
        .update(str, 'utf8')
        .digest(encoding || 'hex');
}

/**
 * Выдает зашифрованный пароль
 * @param pass
 * @returns hash
 */
export function fPassToHash(pass: string): string {
    return fChecksum(pass);
}


/**
 * Генерирует токен
 */
export function fGenerateToken(): string {
    return fChecksum(uniqid());
}
