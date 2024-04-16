/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ClientConnection
*/

#include <gtest/gtest.h>
#include <Error/Error.hpp>
#include <Client/ClientConnection.hpp>

TEST(ErrorHandlingMessage, TestErrorWithMessage)
{
    try {
        ClientConnection::shootManagement("12", "-1");
    } catch (const Error &e) {
        EXPECT_STREQ("Error in Shoot", e.what());
    }
}
