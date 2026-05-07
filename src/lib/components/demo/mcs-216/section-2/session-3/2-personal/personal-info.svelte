<script>
    // Svelte 5 Component (No reactive state needed for static display)
</script>

<!-- Requirement: Set college logo as background image to the web page -->
<main
    class="min-h-auto bg-[url('/college-logo.jpg')] text-black bg-cover bg-no-repeat bg-fixed bg-center p-6 mt-5 rounded-xl"
>
    <!-- Semi-transparent overlay for content readability -->
    <div class="min-h-auto flex items-center justify-center">
        <div
            class="w-full max-w-2xl bg-white/90 backdrop-blur-sm rounded-xl shadow-lg p-6"
        >
            <!-- Requirement: Heading in Arial font, 18px -->
            <h1
                class="font-['Arial'] text-[18px] font-semibold text-center text-gray-900 mb-6"
            >
                Personal Information
            </h1>

            <div class="overflow-x-auto">
                <!-- Requirement: Use tables as when possible -->
                <table class="w-full border-collapse border border-gray-400">
                    <tbody>
                        <!-- Name -->
                        <tr>
                            <!-- Requirement: Yellow background + left aligned field names -->
                            <td
                                class="border border-gray-400 p-3 bg-yellow-400 text-left font-medium w-1/4"
                                >Name:</td
                            >
                            <td class="border border-gray-400 p-3 text-left"
                                >John Doe</td
                            >
                        </tr>

                        <!-- Class -->
                        <tr>
                            <td
                                class="border border-gray-400 p-3 bg-yellow-400 text-left font-medium"
                                >Class:</td
                            >
                            <td class="border border-gray-400 p-3 text-left"
                                >B.Tech Computer Science, 4th Year (Even Sem)</td
                            >
                        </tr>

                        <!-- Qualifications -->
                        <tr>
                            <td
                                class="border border-gray-400 p-3 bg-yellow-400 text-left font-medium"
                                >Qualifications:</td
                            >
                            <td class="border border-gray-400 p-3 text-left"
                                >12th Grade (PCM), Diploma in Full Stack
                                Development</td
                            >
                        </tr>

                        <!-- Photo -->
                        <tr>
                            <td
                                class="border border-gray-400 p-3 bg-yellow-400 text-left font-medium align-top"
                                >Photo:</td
                            >
                            <td
                                class="border border-gray-400 p-3 text-left align-top"
                            >
                                <img
                                    src="/student-photo.jpg"
                                    class="border border-gray-300 rounded-md shadow-sm size-40"
                                    alt="Me"
                                />
                            </td>
                        </tr>

                        <!-- Address -->
                        <tr>
                            <td
                                class="border border-gray-400 p-3 bg-yellow-400 text-left font-medium align-top"
                                >Address:</td
                            >
                            <td class="border border-gray-400 p-3 text-left"
                                >123 University Road, Academic City, State -
                                560001</td
                            >
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</main>
