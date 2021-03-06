//
//  TWebView.h
//  TWebView
//
//  Created by TBD on 2017/7/22.
//  Copyright © 2017年 TBD. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TWebViewConfig.h"

#ifdef __IPHONE_8_0
#import <WebKit/WebKit.h>
#endif


NS_ASSUME_NONNULL_BEGIN

@class TWebView;
@class WKWebView;
@class WKNavigation;
@protocol WKPreviewActionItem;

typedef NS_ENUM(NSUInteger, TWebViewLoadStatus) {
    TWebViewLoadStatusIsLoading = 1,
    TWebViewLoadStatusSuccess   = 2,
    TWebViewLoadStatusFailed    = 3,
};


#pragma mark - TWebViewDelegate

@protocol TWebViewDelegate <NSObject>

@optional

- (BOOL)webView:(TWebView *)webView shouldStartLoadRequest:(NSURLRequest *)request;

- (void)webView:(TWebView *)webView didStartLoadRequest:(NSURLRequest *)request;

- (void)webView:(TWebView *)webView didFinishLoadRequest:(NSURLRequest *)request;

- (void)webView:(TWebView *)webView didFailedLoadRequest:(NSURLRequest *)request withError:(NSError *)error;

- (void)webView:(TWebView *)webView loadStatus:(TWebViewLoadStatus)status title:(NSString *)title;

#pragma mark - 3D Touch Peek & Pop; iOS 10+ available
// Set whether to allow preview url;
// If you return to NO, the following two methods will not run;
// If you return to YES, The following two methods will be run when hard pressed.
- (BOOL)webView:(TWebView *)webView shouldPreviewURL:(nullable NSURL *)url API_AVAILABLE(ios(10.0));

// If you return to nil, the preview link will be made in Safari
// If you do not want to preview the url, please return NO at method "- webView:shouldPreviewURL:"
// param "actions" is the iOS default support actions
- (nullable UIViewController *)webView:(TWebView *)webView previewingViewControllerForURL:(nullable NSURL *)url defaultActions:(NSArray<id <WKPreviewActionItem>> *)actions API_AVAILABLE(ios(10.0));

// Pop the previewing ViewController and then run this method
- (void)webView:(TWebView *)webView commitPreviewingURL:(nullable NSURL *)url controller:(UIViewController *)controller API_AVAILABLE(ios(10.0));

@end


#pragma mark - TWebView

IB_DESIGNABLE

@interface TWebView : UIView

#pragma mark - TWebView Property
@property (nonatomic, weak) id<TWebViewDelegate> _Nullable delegate;
@property (nonatomic, weak) id<TWebViewDelegate> _Nullable commonDelegate;

@property (nonatomic, readonly, strong) UIView *contentWebView;
@property (nonatomic, readonly, strong) UIWebView *uiWebView API_DEPRECATED("Use wkWebView instead, above iOS 8.0, return nil", ios(2.0, 8.0));
@property (nonatomic, readonly, strong) WKWebView *wkWebView API_AVAILABLE(ios(8.0));
@property (nonatomic, readonly, strong) UIScrollView *scrollView;

@property (nonatomic, readonly) BOOL canGoBack;
@property (nonatomic, readonly) BOOL canGoForward;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

// WKWebView title
@property (nullable, nonatomic, readonly, copy) NSString *title API_AVAILABLE(ios(8.0));

// xib or storyboard only (should set before init)
@property (nonatomic, assign) IBInspectable BOOL forceOverrideCookie;

// Progress View
@property (nonatomic, assign, getter=isShowProgress) IBInspectable BOOL showProgress;
@property (nonatomic, strong) IBInspectable UIColor *progressTintColor;
@property (nonatomic, assign) IBInspectable CGFloat progressViewHeight;

// User Interaction
@property (nonatomic, assign) IBCWebViewConfigBlockType selectContentType;
@property (nonatomic, assign) IBCWebViewConfigBlockType scrollChangeSizeType;
// Block ActionSheet & Long Press Menus
@property (nonatomic, assign) IBCWebViewConfigBlockType touchCalloutType;
// only uper ios 8.0
@property (nonatomic, assign) IBCWebViewConfigBlockType scrollBackType API_AVAILABLE(ios(8.0));
// only uper ios 9.0
@property (nonatomic, assign) IBCWebViewConfigBlockType webView3DTouchType API_AVAILABLE(ios(9.0));

// Texts
@property (nonatomic, copy) IBInspectable NSString *confirmText;
@property (nonatomic, copy) IBInspectable NSString *cancelText;
@property (nonatomic, copy) IBInspectable NSString *loadingDefaultTitle;
@property (nonatomic, copy) IBInspectable NSString *successDefaultTitle;
@property (nonatomic, copy) IBInspectable NSString *failedDefaultTitle;

#pragma mark - TWebView Function
- (instancetype)init;
- (instancetype)initWithConfig:(TWebViewConfig *)config;
- (instancetype)initWithFrame:(CGRect)frame;
- (instancetype)initWithConfig:(TWebViewConfig *)config
                         frame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (nullable id<TWebViewDelegate>)getDelegateWithSEL:(SEL)sel;

- (void)reload;
- (void)stopLoading;

- (void)goBack;
- (void)goForward;

- (void)loadRequest:(NSURLRequest *)request;
- (void)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;

- (void)clearCache;

// this forceOverride just once valid
- (void)resetCookieForceOverride:(BOOL)forceOverride;

- (void)getDocumentTitle:(void (^)(NSString * _Nullable title))completion;

// 9.0以及之后，8.0之前可用
- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL;
// 9.0之后可用
- (nullable WKNavigation *)loadFileURL:(NSURL *)URL allowingReadAccessToURL:(NSURL *)readAccessURL API_AVAILABLE(ios(9.0));

// loal local file (single file)
- (void)loadLocalFileInPath:(NSString *)filePath;
// load local file in base path
- (void)loadLocalFileInBasePath:(NSString *)basePath relativeFilePath:(nullable NSString *)relativeFilePath;

+ (nullable NSString *)getJavascriptStringWithFunctionName:(NSString *)function data:(id)data;

- (void)runJavascript:(NSString *)js completion:(void (^ _Nullable)(_Nullable id obj, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END

