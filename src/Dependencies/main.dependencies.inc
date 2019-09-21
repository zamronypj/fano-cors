(*!------------------------------------------------------------
 * [[APP_NAME]] ([[APP_URL]])
 *
 * @link      [[APP_REPOSITORY_URL]]
 * @copyright Copyright (c) [[COPYRIGHT_YEAR]] [[COPYRIGHT_HOLDER]]
 * @license   [[LICENSE_URL]] ([[LICENSE]])
 *------------------------------------------------------------- *)

{-----------------------------------------------
  register application configuration
------------------------------------------------}
container.add(
    'config',
    TJsonFileConfigFactory.create(
        getCurrentDir() + '/config/config.json'
    )
);
//config := container.get('config') as IAppConfiguration;

 {-----------------------------------------------
   register middleware list for global routes that
   need to be use single instance
 ------------------------------------------------}
container.add('appMiddlewares', TMiddlewareCollectionAwareFactory.create());

container.add(
    'cors',
    (TCorsMiddlewareFactory.create())
        .allowedOriginsPatterns(['http\:\/\/localhost\:[0-9]{1,5}'])
        .allowedMethods(['GET', 'POST', 'OPTIONS'])
        .allowedHeaders(['X-My-Custom-Header'])
);

appMiddlewares := container.get('appMiddlewares') as IMiddlewareCollectionAware;
appMiddlewares.addBefore(container.get('cors') as IMiddleware);

container.add(
    GuidToString(IDispatcher),
    TDispatcherFactory.create(
        appMiddlewares,
        container.get(GuidToString(IRouteMatcher)) as IRouteMatcher,
        TRequestResponseFactory.create()
    )
);
