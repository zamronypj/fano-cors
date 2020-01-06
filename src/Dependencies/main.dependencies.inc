(*!------------------------------------------------------------
 * [[APP_NAME]] ([[APP_URL]])
 *
 * @link      [[APP_REPOSITORY_URL]]
 * @copyright Copyright (c) [[COPYRIGHT_YEAR]] [[COPYRIGHT_HOLDER]]
 * @license   [[LICENSE_URL]] ([[LICENSE]])
 *------------------------------------------------------------- *)

 {-----------------------------------------------
   register middleware list for global routes that
   need to be use single instance
 ------------------------------------------------}

container.add(
    'cors',
    (TCorsMiddlewareFactory.create())
        .allowedOriginsPatterns(['http\:\/\/localhost\:[0-9]{1,5}'])
        .allowedMethods(['GET', 'POST', 'OPTIONS'])
        .allowedHeaders(['X-My-Custom-Header'])
);

appMiddlewares := container['appMiddlewares'] as IMiddlewareList;
appMiddlewares.add(container['cors'] as IMiddleware);
